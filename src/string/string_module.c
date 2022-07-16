#include "string_module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string* string_new() {
	struct string* tmp	= (struct string*)calloc(1, sizeof(struct string));
	tmp->data			= NULL;
	tmp->size			= 0;
	return tmp;
}

struct string* string_init(const char* data, int length) {
	struct string* self	= (struct string*)calloc(1, sizeof(struct string));
	self->data			= (char*)calloc(length + 1, sizeof(char));

	memcpy_s(self->data, length, data, length);

	self->size			= length;
	return self;
}

struct string* string_copy(struct string* str) {
	struct string* self	= (struct string*)calloc(1, sizeof(struct string));
	self->data			= (char*)calloc(str->size + 1, sizeof(char));

	memcpy_s(self->data, str->size, str->data, str->size);

	self->size			= str->size;
	return self;
}

struct string* string_move(struct string* tmp) {
	struct string* self	= tmp;
	tmp					= NULL;
	return self;
}

int string_to_int(struct string* self) {
	char* pEnd;
	int ret = strtol(self->data, &pEnd, 10);
	return ret;
}

void string_print(struct string* self) {
	if (self == NULL) {
		printf("Self object is NULL.\n");
		return;
	}

	if (self->data == NULL) {
		printf("String is empty\n");
		return;
	}

	printf("%.*s\n", self->size, self->data);
}

void string_close(struct string* self) {
	if(self == NULL) return;

	if(self->data == NULL) { free(self); return; }

	free(self->data);
	free(self);
}