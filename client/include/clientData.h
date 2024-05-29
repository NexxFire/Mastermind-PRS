/**
 *	\file		clientData.h
 *	\brief		Defines the data structures for the client side of the game.
 *	\author		Your Name
 *	\version	1.0
 *	\date		2022-01-01
 *
 *	\details	This file defines the data structures used by the client, including the game state and the other players' states.
 *              It also defines several constants used in the game, such as the maximum number of rounds and players, the board and result dimensions, and the color codes.
 */
#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include "socketSession.h"

#define MAX_ROUND 12
#define BOARD_WIDTH 4
#define RESULT_WIDTH 2
#define MAX_PLAYERS 4
#define EMPTY -1
#define EMPTY_SCORE -2
#define RED 'R'
#define GREEN 'G'
#define BLUE 'B'
#define YELLOW 'Y'
#define CYAN 'C'
#define MAGENTA 'M'

#define LOG_LEVEL 1
/**
 *	\def LOG(level, fmt, ...)
 *	\brief Macro fonction qui affiche un message de log en fonction du niveau de log.
 */
#define LOG(level, fmt, ...) if (level <= LOG_LEVEL) fprintf(stdout, fmt, ##__VA_ARGS__)

/**
 *	\struct		otherPlayer
 *	\brief		Represents the state of another player in the game.
 */
struct otherPlayer
{
    int nbRound; /**<The number of rounds the other player has played*/
    int nbGoodPlace; /**<The number of colors the other player has placed in the correct positions in the current round*/
    int nbGoodColor; /**<The number of correct colors the other player has placed in the current round, regardless of their positions*/
};
typedef struct otherPlayer otherPlayer_t;


/**
 *	\struct		game
 *	\brief		Represents the state of the game.
 */
struct game
{
    char board[MAX_ROUND][BOARD_WIDTH]; /**<The game board, represented as a 2D array of characters. Each row represents a round, and each column represents a position in the color combination.*/
    char result[MAX_ROUND][RESULT_WIDTH]; /**<result of each round, represented as a 2D array of characters. Each row represents a round, and each column represents a score (number of good places and good colors).*/
    int nbRound; /**<The number of rounds played so far.*/
    otherPlayer_t otherPlayers[MAX_PLAYERS -1]; /**<The states of the other players in the game.*/
    int nbPlayers; /**<The total number of players in the game.*/
    int playerIndex; /**<The index of the current player.*/
    socket_t socket; /**<The socket used for communication with the server.*/
};
typedef struct game game_t;


#endif


