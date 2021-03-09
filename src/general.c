#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#endif

#ifdef _LINUX
#include <unistd.h>
#endif

#include "general.h"


char* c_strdup(const char *s1) {
#ifdef _WIN32
	char* s;
	size_t size;
	size_t eli = sizeof(char);
	size = strlen(s1);
	size++;
	s = (char*) calloc(size, sizeof(char));
	strcpy(s, s1);
	return s;
#else
	return strdup(s1);
#endif
}

char *c_getcwd(char *buffer, int maxlen) {
#ifdef _WIN32
	return _getcwd(buffer, maxlen);
#else
	return getcwd(buffer, maxlen);
#endif
}

void delete_argv(char** argv) {
	int i;
	if(argv) {
		for(i = 0; argv[i]; i++) {
			free(argv[i]);
		}
		free(argv);
	}
}


/*char* c_strcpy(char *dest, const char *src) {
#ifdef _WIN32
	return strcpy_s(dest, _countof(dest), src);
#else
	return strcpy(dest, src);
#endif
}*/
