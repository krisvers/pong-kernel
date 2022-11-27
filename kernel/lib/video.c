#include <video.h>

static char * const vidmem = (char*)0xA0000;
static char * const bufmem = (char*)0x90600;

void pixel_vidmem(int x, int y, char c) {
	bufmem[y * 320 + x] = c;
}

void swap_buffers() {
	for (int i = 0; i < 0xFA00; i++) {
		vidmem[i] = bufmem[i];
	}
}

/*void puts_vidmem(int x, int y, char * string) {
	for (int i = 0; string[i] != 0; i++) {
		vidmem[(((y * 80) + x) * 2) + (i * 2) + 0] = string[i];
		vidmem[(((y * 80) + x) * 2) + (i * 2) + 1] = 0x02;
	}
}*/

void clear_vidmem(void) {
	for (int i = 0; i < 320*200; i++) {
		bufmem[i] = 0x00;
	}
}

char getpixel_vidmem(int x, int y) {
	return bufmem[(((y * 320) + x) * 200)];
}