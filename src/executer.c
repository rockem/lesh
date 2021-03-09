#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#ifdef _LINUX
#include <unistd.h>
#include <sys/wait.h>
#endif

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "hash.h"
#include "executer.h"
#include "lesh_perl.h"
#include "cmd/cd_cmd.h"

extern PerlInterpreter *my_perl;
extern HashList* g_aliases;
extern HashList* g_variables;

static void execSystem(int argc, char** argv);
static char** makeArgs(int argc, char** argv);


void execute_init() {
	char *perl_args[] = {"", "-e", "0", "-w" };
	extern char** environ;
	
	my_perl = perl_alloc();
	perl_construct(my_perl);
	perl_parse (my_perl, xs_init, 3, perl_args, environ);

	hash_set_value(g_aliases, _XS_CD, _XS_CD);
}

void execute_cleanup() {
	perl_destruct(my_perl);
	perl_free(my_perl);
	my_perl = NULL;
}


int execute_command(_command* command) {
	char* alt_command = NULL;
	char** args;
	if(strchr(command->argv[0], SEPERATOR_CHAR) != NULL) {
		execSystem(command->argc, command->argv);
		return 0;
	}
		
	alt_command = hash_get_value(g_aliases, command->argv[0]);
	if(alt_command != NULL) {
		free(command->argv[0]);
		command->argv[0] = c_strdup(alt_command);
	}
	if(strcmp(command->argv[0], "exit") == 0) {
		return 1;
	}
	if(perl_get_cv(command->argv[0], 0)) {
		args = makeArgs(command->argc, command->argv);
		perl_call_argv(command->argv[0], G_DISCARD, args);
		delete_argv(args);
	} else {
		execSystem(command->argc, command->argv);
	}

	return 0;
	
}


static void execSystem(int argc, char** argv) {
	int value;
	int status;
	size_t test_size;
	char* path;
	char* t_path;
	char* path_full = NULL;
	char* path_element = NULL;
	FILE* file;

	if(strchr(*argv, SEPERATOR_CHAR) == NULL) {
		if((t_path = hash_get_value(g_variables, _ENV_PATH)) == NULL) {
			t_path = "";
		}
	} else {
		t_path = "";
	}


	path = c_strdup(t_path);
	t_path = NULL;
	
	path_full = c_strdup(argv[0]);
	path_element = strtok(path, PATH_SEPERATOR_STR);
	while(path_element != NULL) {
		test_size = strlen(path_element) + 1 + strlen(*argv) + 1;
		path_full = realloc(path_full, test_size);
		strcpy(path_full, path_element);
		strcat(path_full, SEPERATOR_STR);
		strcat(path_full, *argv);
		if((file = fopen(path_full, "rt")) != NULL) {
			fclose(file);
			break;
		}
		path_element = strtok(NULL, PATH_SEPERATOR_STR);
	}

	if(path_element == NULL) {
		path_full = realloc(path_full, strlen(*argv) + 1);
		strcpy(path_full, *argv);
	}
	free(path);
		
#ifdef _WIN32
	value = _spawnv( _P_WAIT, argv[0], argv);
#endif
#ifdef _LINUX
	value = fork();
	if(value == 0) {
		execve(path_full, argv, environ);
		perror(path_full);
	} else {
		wait(&status);
		free(path_full);
	}
#endif
}

static char** makeArgs(int argc, char** argv) {
	int i;
	char** args;

	if(argc < 2)
		return NULL;
	args = (char**) malloc(sizeof(char*) * (argc));
	for(i = 0; i < argc - 1; i++) {
		args[i] = c_strdup(argv[i + 1]);
	}
	args[argc - 1] = NULL;

	return args;
}


