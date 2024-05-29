/**
 * \file        serverInit.c
 * \brief       Contains functions for server and player initialization.
 * \details     This file includes functions for initializing the game data and the player data.
 */
#ifndef SERVERINIT_H
#define SERVERINIT_H

#include "serverData.h"

/**
 * \fn          void serverInit(gameData_t *gameData)
 * \brief       Initializes the game data.
 * \param       gameData : The game data structure.
 * \details     This function initializes the game data structure. It sets the number of players to 0, the game winner to EMPTY, and initializes each player's data using the _playerInit function. It also sets the secret code to EMPTY.
 */
void serverInit(gameData_t *gameData);

/**
 * \fn          void _playerInit(player_t *player)
 * \brief       Initializes the player data.
 * \param       player : The player data structure.
 * \details     This function initializes the player data structure. It sets the player's ready status to 0, the number of rounds to 0, and initializes the player's board and result arrays to EMPTY and 0, respectively.
 */
void _playerInit(player_t *player);

#endif