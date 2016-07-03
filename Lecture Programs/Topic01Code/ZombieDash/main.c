#include <string.h>
#include <stdbool.h>
#include "game.h"

// Forward declarations. 
bool args_contain( int argc, char ** argv, char * argument );

/*
 *	Program entry point: plays ZombieDash.
 *
 *	Input:
 *		argc: an integer which records the number of command line arguments
 *		passed to the program.
 *
 *		argv: an array of strings which contains copies of the command line arguments.
 *
 *	Output:
 *		Returns 0 if the program has executed without error.
 */
int main( int argc, char ** argv ) {
	setup_game();

	if ( args_contain( argc, argv, "save-movie" ) ) {
		auto_save_screen = true;
	}

	int turn_result = TURN_OK;

	while ( turn_result != TURN_GAME_OVER ) {
		turn_result = play_turn();

		if ( turn_result == TURN_SCREEN_CHANGED ) {
			draw_game();
		}

		timer_pause( 5 );
	}

	cleanup_game();

	return 0;
}

/*
 *	Deterines if a named argument is present on the command line.
 *
 *	Input:
 *		argc: the number of command line arguments passed to the program.
 *
 *		argv: an array of strings containing the command line argument list.
 *
 *		argument: a string which we are looking for.
 *
 *	Output:
 *		Returns true if and only if the designated argument appears in the
 *		argument list.
 */
bool args_contain( int argc, char ** argv, char * argument ) {
	for ( int i = 0; i < argc; i++ ) {
		if ( strcmp( argument, argv[i] ) == 0 ) {
			return true;
		}
	}

	return false;
}
