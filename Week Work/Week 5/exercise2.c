#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"
#include "Week5Ex2.h"

void setup_zombie(Game * game) {
	game->laps = 0;
	game->over = false;
	game->timer = create_timer(50);
	static char * bitmap =
		"ZZZZ"
		"  Z "
		" Z  "
		"ZZZZ";
	game->zombie = sprite_create(31, 1, 4, 4, bitmap);
	game->zombie->dx = 1.33;
	game->zombie->dy = 0.0;

}

bool update_zombie(Game * game) {
	if (game->over == true) {
		return false;
	}
	else if (!timer_expired(game->timer)) {
		return false;
	}
	else {
		double x_old = round(game->zombie->x);
		sprite_step(game->zombie);
		double x_new = round(game->zombie->x);
		if (x_new >= screen_width()) {
			sprite_move_to(game->zombie, 0, 1);
			game->laps = game->laps + 1;
			if (game->laps >= 3) {
				game->over = true;
			}
		}
		if (x_old != x_new) {
			return true;
		}
		else {
			return false;
		}

	}
	game->over = true;
	return true;
}

void display_zombie(Game * game) {
	sprite_draw(game->zombie);
}

// --------- Do not submit the following functions --------- // 

void zombie_wrap(void) {
	Game game;

	setup_zombie(&game);
	clear_screen();
	display_zombie(&game);
	show_screen();

	while (!game.over) {
		if (update_zombie(&game)) {
			clear_screen();
			display_zombie(&game);
			show_screen();
		}

		timer_pause(25);
	}

	timer_pause(1500);
}

int main(void) {
	setup_screen();
	zombie_wrap();
	cleanup_screen();
	return 0;
}