#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <curses.h>
#include <stdbool.h>

/*
 *	Initialises the player-related aspects of the game,
 *	creating the icon for the player and initialising other state related 
 *	to the player.
 */

void player_setup( void );

/*
 *	Restores the player to its original position and appearance.
 */

void player_reset( void );

/*
 *	Clean up the player module.
 */

void player_cleanup( void );

/*
 *	Interprets the key code and updates the position of the player sprite 
 *	accordingly. 
 *
 *	Input:
 *		key_code:	an integer that represents a key code.
 *
 *	Output:
 *		Returns TRUE if and only if the player moved, indicating that the screen
 *		may need to be refreshed.
 */

bool player_update( int key_code );

/*  
 *	Tests to see if any of the monsters are in the same screen 
 *	location as the player. If yes, a message is displayed and subsequent calls 
 *	to player_dead() will return TRUE until the game is restarted.
 */

void player_check_died();

/* 
 *	Returns true if and only if the player is dead.
 */

bool player_dead();

/**
 *	Draw the player.
 */

void player_draw( void );

#endif
