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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

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

/**
 *	\fn			void signalHandlerRegister (game_t game)
 *	\brief		Registers the signal handlers.
 *	\param 		game : The game state.
 *	\details		Registers the signal handlers for SIGINT and SIGUSR1.
 */
void signalHandlerRegister ();

/**
 *	\fn			void signalHandlerStop(int signum)
 *	\brief		Handles the SIGINT signal.
 *	\param 		signum : The signal number.
 *	\details		Handles the SIGINT signal by sending a message to the server to stop the game and then exiting the client.
 */
void signalHandlerStop(int signum);

/**
 *	\fn			void signalHandlerUSR(int signum)
 *	\brief		Handle client cleanup on exit.
 *	\param 		signum : The signal number.
 *	\details	Remove the client's message queue and send a SIGUSR1 signal to the server to stop the game.
 */
void cleanup();

#endif