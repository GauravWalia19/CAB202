#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cab202_timers.h"

#include "cab202_graphics.h"

void fill_rect(int left, int top, int width, int height, char ch) {
	if (height > 0 && width > 0) {
		for (int i = 0; i < height; i++) {
			draw_line(left, (top + i), (left + width - 1), (top + i), ch);
		}
	}
}

void demo() {
	// Generate coordinates, draw box.
	int x = rand() % screen_width() / 2;
	int y = rand() % screen_height() / 2;
	int w = rand() % (screen_width() - x);
	int h = rand() % (screen_height() - y);
	char * chars = "~!@#$%^&*-+";
	char ch = chars[rand() % strlen(chars)];

	fill_rect(x, y, w, h, ch);

	show_screen();
}

int main(void) {
	setup_screen();
	srand(time(NULL));
	demo();
	timer_pause(5000);
	cleanup_screen();
	return 0;
}