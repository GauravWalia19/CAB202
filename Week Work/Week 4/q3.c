#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"

bool inside_rect(int x, int y, int left, int top, int width, int height) {
	
	bool in = false;
	if ( (x >= left && x <= left + (width - 1)) && (y >= top && y <= (height - 1) + top) ) {
		in = true;
	}
	else {	
		in = false;
	}
	return in;
}

void demo() {
	const int WIDTH = screen_width();
	const int HEIGHT = screen_height();
	const int LEFT = 11;
	const int MARGIN = 5;

	// Generate coordinates, draw box.
	int left = LEFT + MARGIN + rand() % (WIDTH - LEFT - 2 * MARGIN);
	int top = MARGIN + rand() % (HEIGHT - 2 * MARGIN);
	int width = rand() % (WIDTH - left - MARGIN);
	int height = rand() % (HEIGHT - top - MARGIN);

	draw_formatted(0, 0, "left  : %d\n", left);
	draw_formatted(0, 1, "top   : %d\n", top);
	draw_formatted(0, 2, "width : %d\n", width);
	draw_formatted(0, 3, "height: %d\n", height);

	int x = left - MARGIN;

	while (x < left + width + MARGIN) {
		int y = top - MARGIN;

		while (y < top + height + MARGIN) {
			bool inside = inside_rect(x, y, left, top, width, height);

			if (inside) {
				draw_char(x, y, '+');
			}
			else {
				draw_char(x, y, '#');
			}

			y++;
		}

		x++;
	}

	show_screen();
}

int main(void) {
	srand(time(NULL));
	setup_screen();
	demo();
	//timer_pause(2500);
	wait_char();
	cleanup_screen();
	return 0;
}