#include <EXTERN.h>
#include <perl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _LINUX
#include <unistd.h>
#endif
#include "general.h"
#include "hash.h"
#include "parser.h"
#include "executer.h"
#include "getline.h"


HashList* g_aliases;
HashList* g_variables;
PerlInterpreter *my_perl;
_command* comm;

static void fill_variables();

static void delete_command() {
	if(comm) {
		delete_argv(comm->argv);
		free(comm);
		comm = NULL;
	}
}

static void initialize() {
	g_variables = hash_init();
	g_aliases   = hash_init();
	execute_init();
	fill_variables();
}

static void cleanup(void) {
	printf("cleaning up ...\n");
	execute_cleanup();
	hash_cleanup(g_aliases);
	hash_cleanup(g_variables);
	if(comm)
		delete_command();
}

static void fill_variables() {
	int i;
	char* env_var;
	char* e_var;
	char* e_value;
	extern char** environ;
	/* filling our own variable space with export variables */
	for(i = 0; environ[i] != NULL; i++) {
		env_var = _strdup(environ[i]);

		e_var = strtok(env_var, "=");
		if(e_var == NULL) continue;
		e_value = strtok(NULL, "=");
		if(e_value == NULL) continue;

		hash_set_value(g_variables, e_var, e_value);
	}
}

int main(int argc, char** argv) {

	int ex = 0;
	char* line = NULL;
	char buf[256];
	
	initialize();

	atexit(cleanup);
	
	do {
		if(!c_getcwd(buf, sizeof buf)) {
			perror("fatal error");
			break;
		}

		line = getPromptLine(buf);
		comm = parse_line(line);
		if(comm) {
			ex = execute_command(comm); 
			delete_command();
		}
		if(line)
			free(line);
	} while(ex == 0);
	/*cleanup();*/

	return 0;
}
