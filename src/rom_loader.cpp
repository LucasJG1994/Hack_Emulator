#include "rom_loader.h"
#include "log.h"
#include <iostream>
#include <stdio.h>

#define MODULE "ROM"

static int get_rom_ext(const char* file, const char* ext){
	if(file == nullptr) return false;
	if(ext == nullptr) return false;
	for(int i = 0; i < strlen(file); i++){
		if(file[i] == '.'){
			const char* e = &file[i + 1];
			if(strcmp(e, ext) == 0) return true;
			break;
		}
	}
	return false;
}

ROM* rom_load(const char* file){
	if(file == nullptr) return nullptr;
	if(!get_rom_ext(file, "bin")){
		logging(MODULE, "Invalid file format...");
		return nullptr;
	}
	
	ROM* self = new ROM;
	if(self == nullptr){
		logging(MODULE, "Failed to allocate memory...");
		return nullptr;
	}
	
	FILE* fp;
	if(fopen_s(&fp, file, "rb") != 0){
		logging(MODULE, "Failed to load ROM...");
		return nullptr;
	}
	long length;

	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	self->ctx = (char*)calloc(length, sizeof(char));
	if(self->ctx == nullptr){
		logging(MODULE, "Failed to allocate memory...");
		fclose(fp);
		return nullptr;
	}
	self->size = length;
	
	fread(self->ctx, sizeof(char), length, fp);
	fclose(fp);
	
	return self;
}

void rom_close(ROM* self){
	if(self == nullptr) return;
	if(self->ctx == nullptr){
		delete self;
		return;
	}
	
	delete self->ctx;
	delete self;
}
