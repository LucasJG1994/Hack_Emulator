#include "hash_table_module.h"
#include "HackTokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int HASH_TABLE_MIN_SIZE = 32;

static unsigned int hash_function(const char* key) {
	unsigned int hash_value = 0;
	for (const char* p = key; *p != 0; p++) {
		hash_value += (unsigned int)*p;
	}

	hash_value %= HASH_TABLE_MIN_SIZE;
	return hash_value;
}

struct hash_table* hash_table_init() {
	struct hash_table* self = (struct hash_table*)calloc(1, sizeof(struct hash_table));
	if(self == NULL) return NULL;
	self->ctx				= (struct linked_list*)calloc(HASH_TABLE_MIN_SIZE, sizeof(struct linked_list));
	self->size				= HASH_TABLE_MIN_SIZE;
	self->capacity			= 0;
	return self;
}

void hash_table_add(struct hash_table* self, const char* symbol, int length, unsigned int type, unsigned int pos) {
	if(self == NULL) return;
	struct pair* tmp;
	unsigned int hash_val	= hash_function(symbol);
	
	tmp						= (struct pair*)calloc(1, sizeof(struct pair));
	if (tmp == NULL) {
		printf("failed to allocate memory for hash table\n");
		return;
	}
	tmp->key				= string_init(symbol, length);
	tmp->type				= type;
	tmp->lexeme				= string_init(symbol, length);
	tmp->pos				= pos;
	tmp->next				= NULL;

	if (self->ctx[hash_val].head == NULL) {
		self->ctx[hash_val].head	= tmp;
		self->ctx[hash_val].tail	= tmp;
		self->capacity++;
	}
	else {
		self->ctx[hash_val].tail->next	= tmp;
		self->ctx[hash_val].tail		= self->ctx[hash_val].tail->next;
	}
}

void hash_table_add_s(struct hash_table* self, struct string* str, unsigned int type, unsigned int pos) {
	if (self == NULL) return;
	struct pair* tmp;
	unsigned int hash_val = hash_function(str->data);

	tmp = (struct pair*)calloc(1, sizeof(struct pair));
	if (tmp == NULL) {
		printf("failed to allocate memory for hash table\n");
		return;
	}
	tmp->key = string_copy(str);
	tmp->type = type;
	tmp->lexeme = string_copy(str);
	tmp->pos = pos;
	tmp->next = NULL;

	if (self->ctx[hash_val].head == NULL) {
		self->ctx[hash_val].head = tmp;
		self->ctx[hash_val].tail = tmp;
		self->capacity++;
	}
	else {
		self->ctx[hash_val].tail->next = tmp;
		self->ctx[hash_val].tail = self->ctx[hash_val].tail->next;
	}
}

struct pair* hash_table_find(struct hash_table* self, struct string* symbol) {
	if (self == NULL) {
		printf("self is NULL\n");
		return NULL;
	}
	unsigned int hash_val = hash_function(symbol->data);
	if (self->ctx[hash_val].head == NULL) {
		printf("bucket empty\n");
		return NULL;
	}

	struct pair* cur = self->ctx[hash_val].head;
	while (cur != NULL) {
		if (strcmp(cur->key->data, symbol->data) == 0) {
			return cur;
		}
		cur = cur->next;
	}

	printf("key not found\n");
	return NULL;
}

struct hash_table* hash_table_move(struct hash_table* tmp) {
	if (tmp == NULL) return NULL;
	struct hash_table* self	= tmp;
	self					= NULL;
	return self;
}

void hash_table_close(struct hash_table* self) {
	if (self == NULL) return;
	for (int i = 0; i < HASH_TABLE_MIN_SIZE; i++) {
		if (self->ctx[i].head != NULL) {
			struct pair* cur = self->ctx[i].head;
			
			while (cur != NULL) {
				struct pair* del = cur;
				cur				 = cur->next;
				string_close(del->key);
				string_close(del->lexeme);
				free(del);
			}
			
			self->ctx[i].head = NULL;
			self->ctx[i].tail = NULL;
		}
	}
	
	free(self->ctx);
	self->ctx		= NULL;
	self->size		= 0;
	self->capacity	= 0;
	free(self);
}