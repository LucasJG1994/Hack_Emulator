#include "HackScanner.h"
#include "HackParser.h"
#include "vm.h"
#include "symbol_table/symbol_table_singleton.h"
#include "hash_table/hash_table_module.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	
	/*
		TEST CODE
	*/
	//=================================

	if(argc == 2){	
		FILE* fp;
		long long int fp_length;

		if (fopen_s(&fp, argv[1], "r") != 0) {
			printf("Failed to load file...\n");
			return 0;
		}

		fseek(fp, 0L, SEEK_END);
		fp_length = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		const char* code = (const char*)calloc(fp_length + 1, sizeof(char));
		if (code == NULL) {
			printf("Failed to allocate memory for file...\n");
			fclose(fp);
			return 0;
		}

		fread(code, sizeof(char), fp_length, fp);
		fclose(fp);
		
		symbol_table = hash_table_init();
		if (symbol_table == NULL) {
			printf("symbol_table is NULL\n");
			return 0;
		}

		hs_init(code);
		
		//hp_init();
		//hp_start();

		//hp_init();
		//hp_start();

		//vm_init();
		//vm_run();

		hash_table_close(symbol_table);
		free(code);
	}
	else {
		printf("usage: hackemu.exe <file_name>.hack\n");
	}
	return 0;
}