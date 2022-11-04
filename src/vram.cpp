#include "vram.h"
#include "log.h"
#include <minifb.h>
#include <iostream>

#define MODULE "VRAM"

extern unsigned short RAM[32768];

void vram_init(){
	unsigned int palette[2] = { 0xFFFFFFFF, 0x000000FF };
	Window* win = mfb_open("HACK", 512, 256);
	if(win == nullptr){
		logging(MODULE, "Failed to Init Window");
		return;
	}
	
	unsigned int* buffer = new unsigned int[512 * 256];
	while(1){
		
		//Read VRAM data from RAM
		for(int i = 0; i < 8192; i++){
			buffer[(i * 16) + 0]  = palette[(RAM[16382 + i] & 0x0001) ? 1 : 0];
			buffer[(i * 16) + 1]  = palette[(RAM[16382 + i] & 0x0002) ? 1 : 0];
			buffer[(i * 16) + 2]  = palette[(RAM[16382 + i] & 0x0004) ? 1 : 0];
			buffer[(i * 16) + 3]  = palette[(RAM[16382 + i] & 0x0008) ? 1 : 0];
			buffer[(i * 16) + 4]  = palette[(RAM[16382 + i] & 0x0010) ? 1 : 0];
			buffer[(i * 16) + 5]  = palette[(RAM[16382 + i] & 0x0020) ? 1 : 0];
			buffer[(i * 16) + 6]  = palette[(RAM[16382 + i] & 0x0040) ? 1 : 0];
			buffer[(i * 16) + 7]  = palette[(RAM[16382 + i] & 0x0080) ? 1 : 0];
			buffer[(i * 16) + 8]  = palette[(RAM[16382 + i] & 0x0100) ? 1 : 0];
			buffer[(i * 16) + 9]  = palette[(RAM[16382 + i] & 0x0200) ? 1 : 0];
			buffer[(i * 16) + 10] = palette[(RAM[16382 + i] & 0x0400) ? 1 : 0];
			buffer[(i * 16) + 11] = palette[(RAM[16382 + i] & 0x0800) ? 1 : 0];
			buffer[(i * 16) + 12] = palette[(RAM[16382 + i] & 0x1000) ? 1 : 0];
			buffer[(i * 16) + 13] = palette[(RAM[16382 + i] & 0x2000) ? 1 : 0];
			buffer[(i * 16) + 14] = palette[(RAM[16382 + i] & 0x4000) ? 1 : 0];
			buffer[(i * 16) + 15] = palette[(RAM[16382 + i] & 0x8000) ? 1 : 0];
		}

		int state = mfb_update(win, buffer);
		if(state < 0) break;
	}
	
	mfb_close(win);
	delete[] buffer;
}