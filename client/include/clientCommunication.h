/**
 *	\file		clientCommunication.c
 *	\brief		Handles the client-side communication for the game.
 *
 *	\details	This file contains the functions necessary for the client-side communication of the game.
 *				It includes functions for connecting to the server, receiving game results, and fetching data from other clients.
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "socketSession.h"
#include "socketData.h"
#include "utils.h"
#include "clientData.h"
#include <ctype.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 58392

/**
 *	\fn			void connectionWithServer(game_t *game)
 *	\brief		Establishes a connection with the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\note		The user is prompted to enter the server's IP and port. If no input is given, default values are used.
 *  \details    The player is prompted to enter the server's IP and port. If no input is given, default values are used. The player is then prompted to enter 'ready' to indicate that they are ready to play. The number of players and the player's index are then received from the server.
 */
void connexionWithServer(game_t *game);

/**
 *	\fn			void sendCombination(game_t *game)
 *	\brief		Sends the player's color combination to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\note		The player is prompted to enter a combination of colors. The combination is validated before being sent.
 *	\details    The player is prompted to enter a combination of colors. The combination is validated before being sent.
 */
void sendCombination(game_t *game);

/**
 *	\fn			void getResult(game_t *game)
 *	\brief		Gets the result of the current round from the server.
 *	\param 		game : The game structure that contains the game's state.
 *  \details    The result of the current round is received from the server and stored in the game's result array.
 */
void getResult(game_t *game);

/**
 *	\fn			void fetchOtherClientsData(game_t *game)
 *	\brief		Fetches data from other clients connected to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\details    The data of the other clients is received from the server and stored in the game's otherPlayers array.
 */
void fetchOtherClientsData(game_t *game);





#endif