#include "log.h"
#include "cpu.h"

#include <string>

#define MODULE "MAIN"

bool DEBUG = false;

int main(int argc, char** argv){
	if(argc == 2){	
		cpu_init(argv[1]);
	}
	else if(argc == 3){
		std::string option(argv[1]);
		if(option == "-d" || option == "-D"){
			DEBUG = true;
		}
		cpu_init(argv[2]);
	}
	else {
		logging(MODULE, "usage: hackemu <file_name>.bin");
	}
	return 0;
}