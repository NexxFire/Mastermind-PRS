/**
 *	\file		clientCommunication.c
 *	\brief		Handles the client-side communication for the game.
 *
 *	\details	This file contains the functions necessary for the client-side communication of the game.
 *				It includes functions for connecting to the server, receiving game results, and fetching data from other clients.
 */


#include "clientCommunication.h"

/**
 *	\fn			void connectionWithServer(game_t *game)
 *	\brief		Establishes a connection with the server.
 *	\param 		game : The game structure that contains the game's state.
 *  \details    The player is prompted to enter the server's IP and port. If no input is given, default values are used. The player is then prompted to enter 'ready' to indicate that they are ready to play. The number of players and the player's index are then received from the server.
 */
void connexionWithServer(game_t *game) {

    char serverIp[17];
    char serverPortBuffer[7];
    int serverPort;
    char buffer[16];

    printf("Entrez l'adresse IP du serveur : ");
    getUserInput(serverIp, sizeof(serverIp));
    if (strcmp(serverIp, "\n") == 0) {
        strcpy(serverIp, SERVER_IP);
    }

    printf("Entrez le port du serveur : ");
    getUserInput(serverPortBuffer, sizeof(serverPortBuffer));
    if (strcmp(serverPortBuffer, "\n") == 0) {
        serverPort = SERVER_PORT;
    } else {
        serverPort = atoi(serverPortBuffer);
    }
    
    game->socket = connecterClt2Srv(serverIp, serverPort);

    printf("Connected to the server\n");
    printf("type 'ready' when you are ready to play\n");
    do {
        getUserInput(buffer, sizeof(buffer));
    } while (strcmp(buffer, "ready") != 0);
    printf("You are ready to play\n");
    sendData(&(game->socket), "ready", 1);
    printf("Waiting for other players to be ready...\n");
    receiveData(&(game->socket), buffer, 2);
    game->nbPlayers = buffer[0];
    printf("\nThere are %d players in the game\n", game->nbPlayers);
    receiveData(&(game->socket), buffer, 8);
    game->playerIndex = buffer[0];
    printf("You are player %d\n", game->playerIndex +1);
    printf("Game is starting...\n");
    
}

/**
 *	\fn			void sendCombination(game_t *game)
 *	\brief		Sends the player's color combination to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\details    The player is prompted to enter a combination of colors. The combination is validated before being sent.
 */
void sendCombination(game_t *game) {

    char colors[] = "RGBCYM"; // Possible colors
    char playerCombination[BOARD_WIDTH + 2];
    int validCombination = 0;
    do {
        validCombination = 1;
        printf("Player, enter your guess, possible colors are R, G, B, C, Y, and M > ");
        getUserInput(playerCombination, sizeof(playerCombination));
        for (int i = 0; i < BOARD_WIDTH; i++) {
            playerCombination[i] = toupper(playerCombination[i]);
        }
        if (strlen(playerCombination) != BOARD_WIDTH) {
            printf("Error: you must enter exactly 4 colors. Please try again.\n");
            validCombination = 0;
        }
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (strchr(colors, playerCombination[i]) == NULL) {
                printf("Error: the color %c is not valid. Please try again.\n", playerCombination[i]);
                validCombination = 0;
                break;
            }
        }
    } while (!validCombination);
    
    for (int i = 0; i < BOARD_WIDTH; i++) {
        game->board[game->nbRound][i] = playerCombination[i];
    }
    sendData(&(game->socket), playerCombination, 3);
}

/**
 *	\fn			void getResult(game_t *game)
 *	\brief		Gets the result of the current round from the server.
 *	\param 		game : The game structure that contains the game's state.
 *  \details    The result of the current round is received from the server and stored in the game's result array.
 */
void getResult(game_t *game) {
    char buffer[RESULT_WIDTH + 1] = {0};
    receiveData(&(game->socket), buffer, 4);
    for (int i = 0; i < RESULT_WIDTH; i++) {
        game->result[game->nbRound][i] = buffer[i] - '0';
    }
}

/**
 *	\fn			void fetchOtherClientsData(game_t *game)
 *	\brief		Fetches data from other clients connected to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\details    The data of the other clients is received from the server and stored in the game's otherPlayers array.
 */
void fetchOtherClientsData(game_t *game) {
    char buffer[RESULT_WIDTH + 2];
    for (int i = 0; i < game->nbPlayers - 1; i++) {
        receiveData(&(game->socket), buffer, 5);
        game->otherPlayers[i].nbGoodPlace = buffer[0] - '0';
        game->otherPlayers[i].nbGoodColor = buffer[1] - '0';
        game->otherPlayers[i].nbRound = buffer[2] - '0';
    }
}


