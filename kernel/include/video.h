#pragma once

void pixel_vidmem(int x, int y, char c);
void swap_buffers();
//void puts_vidmem(int x, int y, char * c);
void clear_vidmem(void);
char getpixel_vidmem(int x, int y);