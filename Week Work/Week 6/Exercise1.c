#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"

#include "game.h"

// ---------------------------------------------------------------- //

void setup_game(Game * game) {
	// INSERT CODE HERE
	game->score = 0;
	game->over = false;
	game->event_loop_delay = 10;
}

void draw_game(Game * game) {
	// INSERT CODE HERE
}
// ---------------------------------------------------------------- //

void setup_ship(Game * game) {
	// Un-comment the next few lines to use the ship bitmap
	
	static char bitmap[] =
	"======  _  "
	"   \\   / \\ "
	"  ====| o |"
	"   /   \\_/ "
	"======     ";
	

	// INSERT CODE HERE
	game->ship = sprite_create(3, 4, 11, 5, bitmap);
}

bool update_ship(Game * game, int key_code) {
	// INSERT CODE HERE
	double xcord = round(game->ship->x);
	double ycord = round(game->ship->y);

	if (key_code == '1' && xcord > 0) {
		game->ship->x--;
	}
	else if ((key_code == '2') && ((ycord + 5) < screen_height() - 2)) {
		game->ship->y++;
	}
	else if ((key_code == '3') && ((xcord + 11) < 30)) {
		game->ship->x++;
	}
	else if ((key_code == '5') && ycord > 0) {
		game->ship->y--;
	}
	double newxcord = round(game->ship->x);
	double newycord = round(game->ship->y);
	if (newxcord != xcord) {
		return true;
	}
	if (newycord != ycord) {
		return true;
	}

	else {
		return false;
	}

	return false;
}

void draw_ship(Game *game) {
	// INSERT CODE HERE
}

void cleanup_ship(Game * game) {
	// INSERT CODE HERE
}

// ---------------------------------------------------------------- //

void setup_bullet(Game * game) {
	// Un-comment the following line to use the bitmap 
	 static char bitmap[] = { '-' };

	// INSERT CODE HERE
	 game->bullet = sprite_create(0, 0, 1, 1, bitmap);
	 game->bullet->is_visible = false;
	 game->bullet_timer = create_timer(30);
}

void launch_bullet(Game * game) {
	// INSERT CODE HERE
	if (game->bullet->is_visible == true) {
		return;
	}
	if (game->bullet->is_visible == false) {
		game->bullet->x = game->ship->x + 11;
		game->bullet->y = (sprite_height(game->ship) / 2) + game->ship->y;
		game->bullet->dx = 1.0;
		game->bullet->dy = 0.0;
		game->bullet->is_visible = true;
		timer_reset(game->bullet_timer);
	}
}

bool inside_rect(int x, int y, int left, int top, int width, int height) {
	if (x >= left && x < left + width && y >= top && y < top + height) {
		return true;
	}
	else {
		return false;
	}
}

bool move_bullet(Game * game) {
	int newx = 0;
	int newy = 0;
	// INSERT CODE HERE
	if (game->bullet->is_visible == false) {
		return false;
	}
	if (!timer_expired(game->bullet_timer)) {
		return false;
	}
	else {
		//sprite_step(game->bullet);
		game->bullet->x++;
		newx = game->bullet->x;
		newy = game->bullet->y;
		if (newx > (screen_width() - 1) || newy > (screen_height() - 1 ) || (newx < 0) || (newy < 0)) {
			game->bullet->is_visible = false;
		}
		for (int i = 0; i < N_ALIENS; i++) {
			int xloc = game->aliens[i]->x;
			int yloc = game->aliens[i]->y;
			if ((xloc == newx) && (yloc == newy)) {
				game->bullet->is_visible = false;
				game->aliens[i]->is_visible = false;
				game->score++;

			}
		}
		return true;
	}

	
	
}

bool update_bullet(Game * game, int key_code) {
	if (game == NULL)  return false;
	if (game->bullet == NULL) return false;
	if (game->bullet_timer == NULL) return false;

	if (game->bullet->is_visible) {
		return move_bullet(game);
	}
	else if (key_code == ' ') {
		launch_bullet(game);
		return true;
	}
	else {
		return false;
	}
}

void draw_bullet(Game * game) {
	// INSERT CODE HERE
}

void cleanup_bullet(Game * game) {
	// INSERT CODE HERE
}

// ---------------------------------------------------------------- //

void setup_aliens(Game * game, int rock_x[], int rock_y[]) {
	// Un-comment the next line to use the bitmap.
	 static char bitmap[] = { '@' };

	// INSERT CODE HERE
	 for (int i = 0; i < N_ALIENS; i++) {
		 game->aliens[i] = sprite_create(rock_x[i], rock_y[i], 1, 1, bitmap);
		 game->aliens[i]->dy = 1.0;
	 }
	 game->alien_timer = create_timer(350);
}

void draw_aliens(Game * game) {
	// INSERT CODE HERE
}

bool move_alien(sprite_id alien) {
	// INSERT CODE HERE
	if (alien->is_visible == false) {
		return false;
	}
	else {
		int y0 = round(alien->y);
		alien->y += alien->dy;
		int y1 = alien->y;
		if (y1 >= screen_height() - 2) {
			alien->y = 0;
		}
		if (y1 != y0) {
			return true;
		}
		else if (y1 == y0) {
			return false;
		}		

	}
	return false;
}

bool update_aliens(Game * game) {
	if (game == NULL) return false;
	if (game->alien_timer == NULL) return false;

	if (!timer_expired(game->alien_timer)) {
		return false;
	}

	bool changed = false;

	for (int i = 0; i < N_ALIENS; i++) {
		sprite_id alien = game->aliens[i];

		if (alien == NULL) return false;

		changed = move_alien(alien) || changed;
	}

	return changed;
}

void cleanup_aliens(Game * game) {
	// INSERT CODE HERE
}

// --------- Do not submit the following functions --------- // 

/**
*	Gets a random integer that is greater than or equal to
*	first and less than last.
*	Precondition: first < last;
*/
int rand_between(int first, int last) {
	return first + rand() % (last - first);
}

/**
*	Sets up all components of the game.
*/
void setup_all(Game * game) {
	memset(game, 0, sizeof(Game));

	int alien_x[N_ALIENS];
	int alien_y[N_ALIENS];

	for (int i = 0; i < N_ALIENS; i++) {
		alien_x[i] = rand_between(30, screen_width());
		alien_y[i] = rand_between(2, screen_height() - 4);
	}

	setup_game(game);
	setup_ship(game);
	setup_bullet(game);
	setup_aliens(game, alien_x, alien_y);
}

void draw_all(Game * game) {
	clear_screen();
	draw_game(game);
	draw_ship(game);
	draw_bullet(game);
	draw_aliens(game);
	show_screen();
}

void cleanup_all(Game * game) {
	cleanup_ship(game);
	cleanup_bullet(game);
	cleanup_aliens(game);
}

void event_loop(void) {
	Game game;

	setup_all(&game);
	draw_all(&game);

	while (!game.over) {
		int key_code = get_char();

		if (key_code == 'q') {
			game.over = true;
		}
		else {
			bool show_ship = update_ship(&game, key_code);
			bool show_bullet = update_bullet(&game, key_code);
			bool show_aliens = update_aliens(&game);

			if (show_ship || show_bullet || show_aliens) {
				draw_all(&game);
			}

			if (game.score == N_ALIENS) {
				game.over = true;
			}
		}

		timer_pause(game.event_loop_delay);
	}

	cleanup_all(&game);
}

int main(void) {
	srand(time(NULL));
	setup_screen();
	event_loop();
	cleanup_screen();
	return 0;
}