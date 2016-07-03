#pragma once
#include <stdbool.h>
#include "cab202_timers.h"

// Structure to hold game data.
typedef struct Game {
	timer_id timer;
	int score;
	bool over;
} Game;
