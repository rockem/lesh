#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _LINUX
#include <unistd.h>
#endif
#include  "../general.h"
#include "../hash.h"

extern HashList* g_variables;

void cd_cmd(char* path) {
	char* error_msg;
	char* t_path;

	
	if(path == NULL || strcmp(path, "") == 0) {
		if((t_path = hash_get_value(g_variables, "HOME")) == NULL) {
			return;
		}
	} else {
		t_path = c_strdup(path);
	}
	
	if(chdir(t_path) != 0) {
		error_msg = (char*) malloc(3 + strlen(t_path + 1));
		strcpy(error_msg, "cd ");
		strcat(error_msg, t_path);
		perror(error_msg);
		free(error_msg);
	}
}
