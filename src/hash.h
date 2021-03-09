#ifndef __HASH_H
#define __HASH_H

#define _HASH_CHAR_L_A 97
#define _HASH_CHAR_U_A 65

#define _HASH_ARR_SIZE 26

typedef struct __hash_node{
	char* name;
	char* value;
	struct __hash_node* next;
} _hash_node;

typedef struct {
	_hash_node* head;
	_hash_node* tail;
} _hash_list;

typedef struct {
	_hash_list hash_values[_HASH_ARR_SIZE];
} HashList;

extern HashList* hash_init();

extern void hash_cleanup(HashList* list);

extern int hash_set_value(HashList* list, const char* name, const char* value);

extern char* hash_get_value(HashList* list, const char* name);


#endif
