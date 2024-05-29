#ifndef SERVERDATA_H
#define SERVERDATA_H


#include "socketSession.h"
#include "clientData.h"

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

//listen on all network interfaces
#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 58392

#define LOG_LEVEL 1
/**
 * \def         LOG(level, fmt, ...)
 * \brief       Logs a message to the console with a specific level.
*/
#define LOG(level, fmt, ...) if (level <= LOG_LEVEL) fprintf(stdout, fmt, ##__VA_ARGS__)

/**
 * \struct      player
 * \brief       Represents a player.
*/
struct player
{
    char board[MAX_ROUND][BOARD_WIDTH]; /**<The player's board.*/
    char result[MAX_ROUND][RESULT_WIDTH]; /**<The player's result.*/
    int nbRound; /**<The number of rounds played by the player.*/
    socket_t socket; /**<The player's socket to communicate with the client.*/
    int ready; /**<The player's ready status.*/
};
typedef struct player player_t;

/**
 * \struct      playerList
 * \brief       Represents a list of players.
*/
struct playerList
{
    player_t players[MAX_PLAYERS]; /**<The list of players.*/
    int nbPlayers; /**<The number of players in the list.*/
};
typedef struct playerList playerList_t;

/**
 * \struct      gameData
 * \brief       Represents the game data.
*/
struct gameData {
    playerList_t playerList; /**<The list of players.*/
    char secretCode[BOARD_WIDTH]; /**<The secret code.*/
    int gameWinner; /**<The winner of the game.*/
};
typedef struct gameData gameData_t;


#endif