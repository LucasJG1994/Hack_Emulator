#include "log.h"
#include "cpu.h"

#define MODULE "MAIN"

int main(int argc, char** argv){
	//if(argc == 2){	
	//	cpu_init(argv[1]);
	//}
	//else {
	//	logging(MODULE, "usage: hackemu <file_name>.bin");
	//}
	cpu_init("hack.bin");
	return 0;
}