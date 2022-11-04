#ifndef __rom_loader__h
#define __rom_loader__h

struct ROM{
	char* ctx;
	size_t size;
};

ROM* rom_load(const char* file);
void rom_close(ROM* self);

#endif