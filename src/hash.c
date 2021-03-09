#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "hash.h"

static _hash_node* find_node(_hash_list, const char*);
static void insert_node(_hash_list*, _hash_node*);
static int get_name_location(const char*);
static void free_node(_hash_node *node);

HashList* hash_init() {
	int i;
	HashList* list;

	list = (HashList*) malloc(sizeof(HashList));
	
	for(i = 0; i < _HASH_ARR_SIZE + 1; i++) {
		list->hash_values[i].head = NULL;
		list->hash_values[i].tail = NULL;
	}

	return list;
}

void hash_cleanup(HashList* list) {
	int i;
	_hash_node* node;
	_hash_node* tmp_node;
	for(i = 0; i < _HASH_ARR_SIZE + 1; i++) {
		node = list->hash_values[i].head;
		for(; node != NULL;) {
			tmp_node = node->next;
			free_node(node);
			node = tmp_node;			
		}
	}
	free(list);
}

int hash_set_value(HashList* list, const char* name, const char* value) {
	int index;
	_hash_node* node;
	node = find_node(list->hash_values[get_name_location(name)], name);
	
	if(node == NULL) {
		if((node = (_hash_node*) malloc(sizeof(_hash_node))) == NULL)
			return -1;
		if((node->name  = c_strdup(name)) == NULL) {
			free(node);
			return -1;
		}
		if((node->value = c_strdup(value)) == NULL) {
			free(node->name);
			free(node);
			return -1;
		}

		node->next = NULL;
		index = get_name_location(name);
		insert_node(&list->hash_values[index], node);
	} else {
		node->value = (char*) realloc(node->value, sizeof(value) + 1);
		strcpy(node->value, value);
	}
	return 0;
}

char* hash_get_value(HashList* list, const char* name) {
	int index;
	_hash_node* node;
	index = get_name_location(name);
	
	node = find_node(list->hash_values[index], name);
	if(node == NULL) {
		return NULL;
	}

	return node->value;
}

static int get_name_location(const char* name) {
	int location;
	char ch = name[0];
	if(ch >= _HASH_CHAR_L_A)
		location = ch - _HASH_CHAR_L_A;
	else
		location = ch - _HASH_CHAR_U_A;

	if(location < 0 || location >= _HASH_ARR_SIZE)
		return _HASH_ARR_SIZE;

	return location;
}

static _hash_node* find_node(_hash_list list, const char* name) {
	_hash_node* node;
	node = list.head;

	for(; node != NULL && strcmp(node->name, name) != 0; node=node->next);

	return node;
}

static void insert_node(_hash_list* list, _hash_node* node) {
	if(list->head == NULL) {
		list->head = list->tail = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
}

static void free_node(_hash_node *node) {
	free(node->name);
	free(node->value);
	node->next = NULL;
	free(node);
}
