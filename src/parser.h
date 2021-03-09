#ifndef __PARSER_H
#define __PARSER_H

typedef struct {
	char** argv;
	int argc;
} _command;


extern _command* parse_line(const char* line);

#endif
