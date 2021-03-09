#ifndef __GENERAL_H
#define __GENERAL_H

#define _ENV_HOME "HOME"
#define _ENV_PATH "PATH"


extern char* c_strdup(const char *s1);
extern char *c_getcwd(char *buffer, int maxlen);
extern void delete_argv(char** argv);
/*extern char* c_strcpy(char *dest, const char *src);*/

#ifdef _WIN32
#define SEPERATOR_CHAR '\\'
#define SEPERATOR_STR  "\\"
#define PATH_SEPERATOR_STR ";"
#else
#define SEPERATOR_CHAR '/'
#define SEPERATOR_STR  "/"
#define PATH_SEPERATOR_STR ":"
#endif

#endif
