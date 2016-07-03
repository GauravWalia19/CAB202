#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "cab202_sprites.h"
#include <curses.h>

/*	
 *	Sets up the zombies in the game, creating sprites for each,
 *	placing them on the screen at their initial (random) position, and
 *	choosing their initial direction of travel.
 */

void zombie_setup( void );

/*	
 *	Reinitialises the zombies, placing them on the screen at new random 
 *	positions, and choosing their initial direction of travel.
 */

void zombie_reset( void );

/*
 *	Clean up the zombie module.
 */

void zombie_cleanup( void );

/*
 *	Updates the location of all the monsters in the game, including
 *	collision detection with the walls. 
 *
 *	Output:
 *		Returns TRUE if and only if a zombie-related event has changed the 
 *		appearance of the screen, indicating that a refresh may be required.
 */

bool zombie_update( void );

/*
 *	Gets the id of (one of) the zombies at a particular location.
 *
 *	Input:
 *		x, y:	The integer screen coordinates of the location.
 *
 *	Output:
 *		Returns the ID of the first zombie sprite (if any) at the specified
 *		location, or SS_ERROR if there is no zombie at the location.
 */

sprite_id zombie_at( double x, double y );

/**
 *	Draw the zombies.
 */

void draw_zombies( void );

#endif
