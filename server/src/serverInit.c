/**
 * \file        serverInit.c
 * \brief       Contains functions for server and player initialization.
 * \details     This file includes functions for initializing the game data and the player data.
 */
#include "serverInit.h"

/**
 * \fn          void serverInit(gameData_t *gameData)
 * \brief       Initializes the game data.
 * \param       gameData : The game data structure.
 * \details     This function initializes the game data structure. It sets the number of players to 0, the game winner to EMPTY, and initializes each player's data using the _playerInit function. It also sets the secret code to EMPTY.
 */
void serverInit(gameData_t *gameData) {
    LOG(1, "Initializing game data...\n");
    gameData->playerList.nbPlayers = 0;
    gameData->gameWinner = EMPTY;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        _playerInit(&gameData->playerList.players[i]);
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        gameData->secretCode[i] = EMPTY;
    }
    LOG(1, "Game data initialized.\n");
}

/**
 * \fn          void _playerInit(player_t *player)
 * \brief       Initializes the player data.
 * \param       player : The player data structure.
 * \details     This function initializes the player data structure. It sets the player's ready status to 0, the number of rounds to 0, and initializes the player's board and result arrays to EMPTY and 0, respectively.
 */
void _playerInit(player_t *player) {
    player->ready = 0;
    player->nbRound = 0;
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            player->board[i][j] = EMPTY;
        }
        for (int j = 0; j < RESULT_WIDTH; j++) {
            player->result[i][j] = 0;
        }
    }
}