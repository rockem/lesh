#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "getline.h"



#ifdef _LINUX
char* getPromptLine(char* prompt) {
	char*   line = NULL;
	char*   o_line = NULL;
	size_t  len = 0;
	ssize_t read;

	printf("lesh:%s>>", prompt);
	read = getline(&line, &len, stdin);
	line[strlen(line) - 1] = '\0';
	o_line = c_strdup(line);
	free(line);

	return o_line;
}
#endif
#ifdef _WIN32
char* getPromptLine(char* prompt) {
	char    buffer[LINE_SIZE];
	char*   o_line = NULL;

	printf("lesh:%s>>", prompt);
	gets(buffer);
	o_line = c_strdup(buffer);

	return o_line;
	/* return o_line; */
}
#endif
