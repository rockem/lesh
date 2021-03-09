#ifndef __EXECUTER_H
#define __EXECUTER_H

#include "parser.h"

#define _LESH_CD "cd"


extern void execute_init();

extern void execute_cleanup();

extern int execute_command(_command* command);


#endif
