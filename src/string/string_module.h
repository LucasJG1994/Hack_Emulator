#ifndef __string_module__h
#define __string_module__h

struct string {
	char*  data;
	unsigned int size;
};

struct string* string_new();
struct string* string_init(const char* data, int length);
struct string* string_copy(struct string* str);
struct string* string_move(struct string* tmp);
int			   string_to_int(struct string* self);
void		   string_print(struct string* self);
void		   string_close(struct string* self);

#endif