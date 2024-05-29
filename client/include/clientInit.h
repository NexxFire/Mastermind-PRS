/**
 *	\file		clientInit.c
 *	\brief		Initializes the game state for the client.
 *
 *	\details	This file contains the functions necessary for initializing the game state on the client side.
 */
#ifndef INIT_H
#define INIT_H

#include "clientData.h" // client/include/clientData.h

/**
 *	\fn			void _initBoard(char board[MAX_ROUND][BOARD_WIDTH])
 *	\brief		Initializes the game board.
 *	\param 		board : The game board to be initialized.
 *	\result		The game board is filled with the EMPTY constant.
 */
void _initBoard(char board[MAX_ROUND][BOARD_WIDTH]);

/**
 *	\fn			void _initResult(char result[MAX_ROUND][RESULT_WIDTH])
 *	\brief		Initializes the result array.
 *	\param 		result : The result array to be initialized.
 *	\result		The result array is filled with the EMPTY_SCORE constant.
 */
void _initResult(char result[MAX_ROUND][RESULT_WIDTH]);

/**
 *	\fn			void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS-1])
 *	\brief		Initializes the array of other players.
 *	\param 		otherPlayers : The array of other players to be initialized.
 *	\result		The number of rounds, good places, and good colors for each other player is set to 0.
 */
void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS-1]);

/**
 *	\fn			void initGame(game_t *game)
 *	\brief		Initializes the game state.
 *	\param 		game : The game state to be initialized.
 *	\result		The number of players and rounds in the game state is set to 0, and the game board, result array, and other players array are initialized.
 */
void initGame(game_t *game);

#endif