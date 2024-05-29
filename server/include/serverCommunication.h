/**
 * \file        serverCommunication.c
 * \brief       Contains functions for server-client communication.
 * \details     This file includes functions for client registration, receiving player choices, sending results, and handling threads for listening to clients and ensuring client readiness.
 */
#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include "serverData.h"
#include "socketData.h"
#include "utils.h"
#include "socketSession.h"
#include <pthread.h>
#include <unistd.h>

/**
 * \struct      listenningThreadHandlerArgs
 * \brief       Represents the arguments for the listenning thread handler.
*/
struct listenningThreadHandlerArgs {
    gameData_t *gameData; /**<The game data structure.*/
    pthread_t *threadClients; /**<The client threads.*/
    int *gameStarted; /**<The game started flag.*/
};
typedef struct listenningThreadHandlerArgs listenningThreadHandlerArgs_t;

/**
 * \struct      clientReadyThreadHandlerArgs
 * \brief       Represents the arguments for the client ready thread handler.
*/
struct clientReadyThreadHandlerArgs {
    gameData_t *gameData; /**<The game data structure.*/
    int playerIndex; /**<The index of the player.*/
};
typedef struct clientReadyThreadHandlerArgs clientReadyThreadHandlerArgs_t;

/**
 * \fn          void clientRegistration(gameData_t *gameData)
 * \brief       Handles client registration.
 * \param       gameData : The game data structure.
 * \details     This function waits for players to connect and creates a new thread for each player. It also sends the number of players and their respective IDs to each player.
 */
void clientRegistration(gameData_t *gameData);

/**
 * \fn          void getPlayerChoice(gameData_t *gameData, int playerIndex)
 * \brief       Receives the player's choice.
 * \param       gameData : The game data structure.
 * \param       playerIndex : The index of the player in the player list.
 * \details     This function waits for a specific player to send their choice and then updates the player's board with their choice.
 */
void getPlayerChoice(gameData_t *gameData, int playerIndex);

/**
 * \fn          void sendResult(gameData_t *gameData, int playerIndex)
 * \brief       Sends the result to the player.
 * \param       gameData : The game data structure.
 * \param       playerIndex : The index of the player in the player list.
 * \details     This function sends the result of the current round to the player and also sends the results of other players to the player.
 */
void sendResult(gameData_t *gameData, int playerIndex);

/**
 * \fn          void *_listenningThreadHandler(void *args)
 * \brief       Handles the listening thread.
 * \param       args : The arguments for the thread.
 * \details     This function listens for players to connect until the maximum number of players is reached or the game has started. It creates a new thread for each connected player.
 */
void *_listenningThreadHandler(void *args);

/**
 * \fn          void *_clientReadyThreadHandler(void *args)
 * \brief       Handles the client ready thread.
 * \param       args : The arguments for the thread.
 * \details     This function waits for a specific player to be ready. Once the player is ready, it updates the player's ready status in the game data.
 */
void *_clientReadyThreadHandler(void *args);

#endif