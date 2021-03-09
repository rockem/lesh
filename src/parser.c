#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "general.h"
#include "parser.h"
#include "hash.h"


static int resizeArray(char***, int, int);
static void execSystem(char**, int);

_command* parse_line(const char* line) {
	_command* command;
	char* token;
	char* tmp_line;

	if(line == NULL || strcmp(line, "") == 0)
		return NULL;

	command = (_command*) malloc(sizeof(_command));
 	if(command == NULL)
		return NULL;

	command->argc = 1;
	tmp_line = c_strdup(line);
	token = strtok(tmp_line, " ");

	command->argv = (char**) malloc(sizeof(char*) * 2);
	command->argv[0] = c_strdup(token);
	command->argv[1] = NULL;

	while((token = strtok(NULL, " ")) != NULL) {
		command->argc++;

		resizeArray(&command->argv, command->argc, command->argc + 1);
		command->argv[command->argc - 1] = c_strdup(token);
		command->argv[command->argc] = NULL;
	}

	return command;
}

static int resizeArray(char*** arr, int origSize, int newSize) {
	int i;
	char** tmp_arr;

	tmp_arr = (char**) calloc(sizeof(char*), sizeof(char*) * (origSize - 1));
	if(tmp_arr == NULL)
		return -1;

	for(i = 0; i < origSize - 1; i++) {
		tmp_arr[i] = (*arr)[i];
	}
	
	if((*arr = (char**) realloc(*arr, sizeof(char*) * newSize)) == NULL)
		return -1;

	for(i = 0; i < origSize - 1; i++) {
		(*arr)[i] = tmp_arr[i];
	}

	free(tmp_arr);
	tmp_arr = 0;

	return 0;
}


