/**
 *	\file		server.c
 *	\brief		Defines the main server logic for the game.
 *
 *	\details	This file defines the main server logic for the game, including the main function, the game loop, and the functions for creating the secret code, starting the game, checking the player's choice, ending the game, and handling the client threads.
 */
#ifndef SERVER_H
#define SERVER_H

#include "serverData.h"
#include "serverCommunication.h"
#include "serverInit.h"
#include <stdlib.h>

/**
 * \def         MAX(a,b)
 * \brief       Returns the maximum of two values.
 */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

/**
 * \struct      clientThreadHandlerArgs
 * \brief       Represents the arguments for the client thread handler.
*/
struct clientThreadHandlerArgs
{
    gameData_t *gameData; /**<The game data structure.*/
    int playerIndex; /**<The index of the player.*/
};
typedef struct clientThreadHandlerArgs clientThreadHandlerArgs_t;


/**
 * \fn          void createCombinations(gameData_t *gameData)
 * \brief       Creates the secret code.
 * \param       gameData : The game data structure.
 * \details     This function generates a random secret code and stores it in the gameData's secretCode array.
 */
void createCombinations(gameData_t *gameData);

/**
 * \fn          void startGame(gameData_t *gameData)
 * \brief       Starts the game and manages client threads.
 * \param       gameData : The game data structure.
 * \details     This function starts the game by creating a new thread for each player to handle their game session.
 */
void startGame(gameData_t *gameData);

/**
 * \fn          void checkChoice(gameData_t *gameData, int playerIndex)
 * \brief       Checks the player's choice.
 * \param       gameData : The game data structure.
 * \param       playerIndex : The index of the player.
 * \details     This function checks the player's choice against the secret code and updates the player's result in the game data.
 */
void checkChoice(gameData_t *gameData, int playerIndex);

/**
 * \fn          void endGame(gameData_t *gameData)
 * \brief       Ends the game.
 * \param       gameData : The game data structure.
 * \details     This function ends the game by determining the winner and sending the result to all players.
 */
void endGame(gameData_t *gameData);

/**
 * \fn          void *clientThreadHandler(void *args)
 * \brief       Handles the client threads.
 * \param       args : The arguments for the client thread handler.
 * \details     This function handles the player's game session. The player's choice is checked, and the result is sent to the player. The thread ends when the player has reached the maximum number of rounds or when the game has a winner.
 */
void *clientThreadHandler(void *args);




#endif