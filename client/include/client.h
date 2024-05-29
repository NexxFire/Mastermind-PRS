/**
 *	\file		client.c
 *	\brief		Handles the main game loop for the client.
 *
 *	\details	This file contains the main game loop and the functions for checking if the game is over and ending the game.
 */
#ifndef CLIENT_H
#define CLIENT_H


#include "clientData.h" 
#include "clientInit.h" 
#include "clientShow.h" 
#include "clientCommunication.h" 
#include "socketData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 *	\fn			int isGameOver(game_t game)
 *	\brief		Checks if the game is over.
 *	\param 		game : The game state.
 *	\details		Returns 1 if the game is over (either the player has found the secret combination, the maximum number of rounds has been reached, or another player has found the secret combination), and 0 otherwise.
 */
int isGameOver(game_t game);

/**
 *	\fn			void endGame(game_t game)
 *	\brief		Ends the game.
 *	\param 		game : The game state.
 *	\details		Displays a message indicating whether the player has won or lost, who the winner is (if there is one), and what the secret combination was.
 */
void endGame(game_t game);

#endif