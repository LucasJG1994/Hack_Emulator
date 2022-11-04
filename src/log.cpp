#include "log.h"
#include <iostream>

void logging(const char* mod, const char* msg){
	std::cout << "[ " << ((mod == nullptr) ? "NULL": mod) << " ] " <<  ((msg == nullptr) ? "NULL": msg) << std::endl;
}