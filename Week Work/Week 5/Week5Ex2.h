#pragma once
#include <stdbool.h>
#include "cab202_timers.h"
#include "cab202_sprites.h"

// Structure to hold game data.
typedef struct Game {
	timer_id timer;
	sprite_id zombie;
	int laps;
	bool over;
} Game;
