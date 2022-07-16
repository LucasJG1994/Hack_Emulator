#ifndef __hash_table_module__h
#define __hash_table_module__h

#include "string/string_module.h"

struct pair {
	struct string* key;
	unsigned int   type;
	struct string* lexeme;
	unsigned int   pos;
	struct pair*   next;
};

struct linked_list {
	struct pair* head;
	struct pair* tail;
};

struct hash_table {
	unsigned int		size;
	unsigned int		capacity;
	struct linked_list* ctx;
};

struct hash_table*	hash_table_init();
void				hash_table_add(struct hash_table*   self, const char* symbol, int length, unsigned int type, unsigned int pos);
void				hash_table_add_s(struct hash_table* self, struct string* str, unsigned int type, unsigned int pos);
struct pair*		hash_table_find(struct hash_table*  self, struct string* symbol);
struct hash_table*	hash_table_move(struct hash_table* tmp);
void				hash_table_close(struct hash_table* self);

#endif