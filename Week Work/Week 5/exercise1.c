#include <stdbool.h>
#include <stdlib.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"
#include "Week5Ex1.h"

void setup_score(Game * game) {
	game->score = 0;
	game->over = false;
	game->timer = create_timer(90);
}

bool update_score(Game * game) {
	if (timer_expired(game->timer)) {
		game->score = game->score + 1;
		if (game->score >= 48) {
			game->over = true;
		}
		return true;
	}

	return false;
}

void display_score(Game * game) {
	if (game->over == false) {
		draw_formatted(8, 6, "Score: %d", game->score);
		draw_formatted(8, 7, "Clock time: %f", get_current_time());
	}
	else if (game->over == true) {
		draw_formatted(8, 6, "Game over! Final score: %d", game->score);
		draw_formatted(8, 7, "Clock time: %f", get_current_time(game->timer));
	}
}

void simple_timer(void) {
	Game game;
	setup_score(&game);
	while (!game.over) {
		if (update_score(&game)) {
			clear_screen();
			display_score(&game);
			show_screen();
		}
		timer_pause(20);
	}
	timer_pause(1500);
}
int main(void) {
	setup_screen();
	simple_timer();
	cleanup_screen();
	return 0;
}