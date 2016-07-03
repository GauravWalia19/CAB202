/*
* CAB202 Assignment1 - Zombie Jump
*
* Author: Tom Stark
* Student Number: 9499776
*/
#include "cab202_graphics.h"
#include "cab202_timers.h"
#include "cab202_sprites.h"

//Forward declarations of functions
void Debugger();
void Setup();
void EventLoop();
void SetupBlocks();
void SetupPlayer();
void DrawBlocks();
void DrawPlayer();
void DrawHUD();
void UpdateTime();
void StepBlocks();
void ProcessOnBlock();
void ProcessOffBlock();
void ProcessInput();
void KeepPlayerInGameArea();
void KillPlayer();
bool GameOver();
void PlayAgain();
void ProcessLevel();

//Global Variables
bool debug = false;
bool over;
int lives;
int timeMinutes;
int timeSeconds;
int level;
int score;
bool display = true;
double gravity = 2.0;
bool setOnBlock;

//constants
#define NUMBEROFBLOCKS 150

//timers used
timer_id gametime; //used for the game time timer 
timer_id blocktime; //used for the block time timer
timer_id playertime; //used for the player


//strites that are going to be used
sprite_id player;
sprite_id blocks[NUMBEROFBLOCKS];


int main(void) {
	setup_screen(); ////Sets up the terminal display for curses-based graphics
	//auto_save_screen = true;
	EventLoop(); //loop for the game
	PlayAgain();
	cleanup_screen(); //Restore the terminal to its normal operational state
}

void Debugger() {
	// Player Stats
	draw_string(0, 2, "Player:");
	draw_formatted(2, 3, "X: %g @ %g", player->x, player->dx);
	draw_formatted(2, 4, "Y: %g @ %g", player->y, player->dy);
}

void EventLoop(void) {
		Setup();        //set the values of all the starting varaiables, sets up all the sprites (blocks and player)
		while (over == false) {
			//clear the screen
			clear_screen();

			// Debugger
			if (debug) { Debugger(); }

			//update the game time
			UpdateTime();

			//Check if the player is on a block (move him UP 2 blocks)
			ProcessOnBlock();

			//move all the blocks up 
			StepBlocks();

			//Check if the player is NOT on a block (move him DOWN 2 blocks)
			ProcessOffBlock();

			//draw everything 
			DrawHUD();
			DrawBlocks();
			DrawPlayer();

			//makes sure player can't jump outside the game area
			KeepPlayerInGameArea();
			
			//if dead setupblocks setup player
			KillPlayer();
			
			//check if the user has input a level change
			ProcessLevel(get_char());

			//show screen
			show_screen();

			over = GameOver();

			//pause the timer to give the cpu a rest (this value may need to be increased depending on the processing power of the computer playing the game
			//in order to satisfy the requirement of the game display screen being entirely visible at all times) (It runs fine with these settings on my 
			//desktop PC(i7) but flashes a bit on my laptop(i3))
			timer_pause(150);
	}
}

void Setup() {
	//set all the global variables
	over = false;
	lives = 3;
	level = 1;
	score = 0;	
	timeMinutes = 0;
	timeSeconds = 0;
	gametime = create_timer(1000);
	blocktime = create_timer(1000);
	playertime = create_timer(1000);
	display = true;
	setOnBlock = true;	
	//setup blocks
	SetupBlocks();
	//setup player
	SetupPlayer();

}

void SetupBlocks() {
	if (level == 1) {
		srand(time(NULL));
		double yValue = screen_height() + 1; // worked with 1
		static char * bitmap1 =
			"================="
			"=================";
		static char * bitmap2 =
			"*****************"
			"*****************";
		for (int i = 1; i < NUMBEROFBLOCKS; i++) {
			int goodOrBad = (rand() % 3) + 1;
			double randomXvalue = rand() % (screen_width() - 7 - 1) + 1;

			blocks[0] = sprite_create(randomXvalue, screen_height() - 7, 7, 2, bitmap1); //was -3 //-7 works on both levels but still bounces on first block on second level
			if (goodOrBad == 1 || goodOrBad == 2) {
				blocks[i] = sprite_create(randomXvalue, yValue, 7, 2, bitmap1);
	
			}
			else if (goodOrBad == 3) {
				blocks[i] = sprite_create(randomXvalue, yValue, 7, 2, bitmap2);
			
			}

			yValue += 4.0; // the next will be off the screen
			blocks[i]->dx = 0.0;
			blocks[i]->dy = -2.0;
			blocks[0]->dy = -2.0;
		}
	}
	if (level == 2) {
		srand(time(NULL));
		double yValue = screen_height() + 1;
		static char * bitmap1 =
			"================="
			"=================";
		static char * bitmap2 =
			"*****************"
			"*****************";
		for (int i = 1; i < NUMBEROFBLOCKS; i++) {
			int randomblocklength = (rand() % 8) + 3; //was 11
			int goodOrBad = (rand() % 3) + 1;
			double randomXvalue = rand() % (screen_width() - 10 - 1) + 1;

			blocks[0] = sprite_create(randomXvalue, screen_height() - 3, randomblocklength, 2, bitmap1);
			if (goodOrBad == 1 || goodOrBad == 2) {
				blocks[i] = sprite_create(randomXvalue, yValue, randomblocklength, 2, bitmap1);
				
			}
			else if (goodOrBad == 3) {
				blocks[i] = sprite_create(randomXvalue, yValue, randomblocklength, 2, bitmap2);
				
			}

			yValue += 4.0; // the next will be off the screen
			blocks[i]->dx = 0.0;
			blocks[i]->dy = -2.0;
			blocks[0]->dy = -2.0;
		}
	}
}

void DrawBlocks() {
	for (int i = 0; i < NUMBEROFBLOCKS; i++) {
		sprite_draw(blocks[i]);
	}
}

void SetupPlayer() {
	static char * bitmap =
		"o"
		"|"
		"M";
	player = sprite_create(blocks[0]->x + 2, blocks[0]->y - 3, 1, 3, bitmap); //spawn the player on the starting block which is going to be safe

	player->dx = 0.0;
	player->dy = 0.0;
}

void DrawPlayer() {
	sprite_draw(player);
}

void DrawHUD() {
	draw_formatted(0, 0, "Lives Remaining: %d", lives);
	draw_formatted(screen_width() - 18, 0, "Game Time: %d:%02d", timeMinutes, timeSeconds);
	draw_formatted(0, screen_height() - 1, "Level: %d", level);
	draw_formatted(10, screen_height() - 1, "Score: %d", score);
	draw_formatted(20, screen_height() - 1, "Press the 'L' Key to go up a level");
	draw_line(0, 1, screen_width(), 1, '-');
	draw_line(0, screen_height() - 2, screen_width(), screen_height() - 2, '-');
}

void UpdateTime() {
	if (timer_expired(gametime)) {
		timeSeconds++;
	}
	if (timeSeconds == 60) {
		timeSeconds = 0;
		timeMinutes++;
	}
}

void StepBlocks() {
	if (timer_expired(blocktime)) {
	for (int i = 0; i < NUMBEROFBLOCKS; i++) {
			sprite_step(blocks[i]);
			if (blocks[i]->y < 2 || blocks[i]->y > screen_height() - 2) {
				blocks[i]->is_visible = false;
			}
			else {
				blocks[i]->is_visible = true;
			}
		}
	}
}

void ProcessOnBlock() {	
	static char * bitmap2 =
		"*****************"
		"*****************";
	static char * bitmap1 =
		"================="
		"=================";
	for (int i = 0; i < NUMBEROFBLOCKS; i++) {		
		//test if player is on a block
		if (((player->y == blocks[i]->y - 3) || (player->y == blocks[i]->y - 1)) && ((player->x >= blocks[i]->x) && (player->x <= blocks[i]->x + sprite_width(blocks[i]) - 1))) {
			gravity = 2.0;
			sprite_turn_to(player, 0.0, -2.0); //going up
			if ((blocks[i]->bitmap == bitmap1)) {
				
				if (blocks[i]->y - 3 == player->y) {
					if (setOnBlock == false && (player->y != blocks[0]->y - 3)) { //and the player is not on the first block
						score = score + 1;
						setOnBlock = true;
					}
				}
			}
			if (blocks[i]->bitmap == bitmap2) {
				lives--;
				//setup blocks
				SetupBlocks();
				//setup player
				SetupPlayer();
			}
			if (timer_expired(playertime)) {
				sprite_step(player);
			}
			sprite_turn_to(player, 0.0, 0.0);
			//read in user input and move the player (player can only move if on a block)
			ProcessInput(get_char());
		}
	}

}

void ProcessOffBlock() {
	for (int i = 0; i < NUMBEROFBLOCKS; i++) {
		if (player->y - 1 > blocks[i]->y) {  
			//DO SOMETHING HERE FOR THE SCORE 
			setOnBlock = false;			
			if (level == 1) {
				setOnBlock = false;
				sprite_turn_to(player, 0.0, 2.0);
				if (timer_expired(playertime)) {
					sprite_step(player);
				}
				sprite_turn_to(player, 0.0, 0.0);
			}
			if (level == 2) {
				setOnBlock = false;
				sprite_turn_to(player, 0.0, gravity);
				if (timer_expired(playertime)) {
					sprite_step(player);
					gravity += 2;
				}
				sprite_turn_to(player, 0.0, 0.0);
			}
		}
	}
}

void ProcessInput(int key_in) {

	if (key_in == KEY_LEFT) {
		player->x--;
	}
	else if (key_in == KEY_RIGHT) {
		player->x++;
	}
	else if (key_in == 'l') {
		level = 2;
		//setup blocks
		SetupBlocks();
		//setup player
		SetupPlayer();
	}
}

void KeepPlayerInGameArea() {
	if (player->x >= screen_width()) {
		player->x = screen_width() - 1;
	}
	if (player->x < 0) {
		player->x = 0;
	}
}

void KillPlayer() {
	if (player->y < 2) {
		lives--;
		//setup blocks
		SetupBlocks();
		//setup player
		SetupPlayer();
	}
	if (player->y + 3 > screen_height() - 2) {
		lives--;
		//setup blocks
		SetupBlocks();
		//setup player
		SetupPlayer();
	}
}

bool GameOver() {
	if (lives < 1) {
		return true;
	}
	return false;
}

void PlayAgain() {
	clear_screen();
	while (display == true) {
		draw_formatted(10, screen_height() / 2, "Press 'r' to restart the game or 'q' to quit the game");
		int answer;
		answer = get_char();

		if (answer == 'r') {
			
			EventLoop();
			PlayAgain();
			
		}
		else if (answer == 'q') {
			display = false;
			return;
		}
	}
}

void ProcessLevel(int key_in) {

	if (key_in == 'l') {
		level = 2;
		//setup blocks
		SetupBlocks();
		//setup player
		SetupPlayer();
	}
}




