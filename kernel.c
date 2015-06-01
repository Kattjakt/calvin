//#include <stdint.h>
#include <stddef.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 25

struct Screen {
	size_t row, column;
	char *buffer;
};

struct Screen screen;

int screeninit() {
	screen.buffer = (char*)0xB8000;
	screen.row = 0;
	screen.column = 0;
}

int kputchar(char c, char color) {
	if (c == '\n' || c == '\r') {
		screen.column = 0;
		screen.row++;
	} else {
		screen.buffer[2 * (screen.row * MAX_WIDTH + screen.column)] = c;
		screen.buffer[2 * (screen.row * MAX_WIDTH + screen.column) + 1] = color;
		screen.column ++;
		if (screen.column > MAX_WIDTH) {
			screen.column = 0;
			screen.row++;
		}	
	}
	return 1; 
}

void kclrscr() {
	screen.column = 0;
	screen.row = 0;
	
	for (int i = 0; i < MAX_WIDTH * MAX_HEIGHT * 2; i++) {
		kputchar(' ', 0x07);
	}
	
	screen.column = 0;
	screen.row = 0;
}

void kmain(void) {
	screeninit();
	kclrscr();

	kputchar('A', 0x07);	
	kputchar('B', 0x07);
	kputchar('\n', 0x07);
	kputchar('C', 0x07);
	kputchar('D', 0x07);

	return;
}
