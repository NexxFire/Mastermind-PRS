/**
 *	\file		server.c
 *	\brief		Defines the main server logic for the game.
 *
 *	\details	This file defines the main server logic for the game, including the main function, the game loop, and the functions for creating the secret code, starting the game, checking the player's choice, ending the game, and handling the client threads.
 */
#include "server.h"


 /**
 * \fn          int main()
 * \brief       Main function of the server.
 * \details     This function initializes the game data and enters the main game loop, which includes the client registration, the creation of the secret code, the start of the game, and the end of the game.
 */
int main() {
    gameData_t gameData;
    while (1) {
        serverInit(&gameData);
        clientRegistration(&gameData);
        createCombinations(&gameData);
        startGame(&gameData);
        endGame(&gameData);
    }
    return 0;
}

/**
 * \fn          void createCombinations(gameData_t *gameData)
 * \brief       Creates the secret code.
 * \param       gameData : The game data structure.
 * \details     This function generates a random secret code and stores it in the gameData's secretCode array.
 */
void createCombinations(gameData_t *gameData) {
    LOG(1, "Creating secret code...\n");
    char * colors = "RGBCYM";
    srand(time(NULL));
    for (int i = 0; i < BOARD_WIDTH; i++) {
        gameData->secretCode[i] = colors[rand() % strlen(colors)];
    }
    LOG(1, "Secret code created.\n");
    LOG(1, "Secret code : ");
    for (int i = 0; i < BOARD_WIDTH; i++) {
        LOG(1, "%c", gameData->secretCode[i]);
    }
    LOG(1, "\n");
}


/**
 * \fn          void startGame(gameData_t *gameData)
 * \brief       Starts the game and manages client threads.
 * \param       gameData : The game data structure.
 * \details     This function starts the game by creating a new thread for each player to handle their game session.
 */
void startGame(gameData_t *gameData) {
    LOG(1, "Starting game...\n");
    pthread_t threadClients[MAX_PLAYERS];
    clientThreadHandlerArgs_t clientThreadHandlerArgs[MAX_PLAYERS];
    
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        clientThreadHandlerArgs[i].gameData = gameData;
        clientThreadHandlerArgs[i].playerIndex = i;
        pthread_create(&threadClients[i], 
                        NULL, 
                        clientThreadHandler, 
                        &clientThreadHandlerArgs[i]);
        LOG(1, "Thread for player %d created.\n", i);
    }
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
    }
    LOG(1, "All players have ended their game.\n");
}

/**
 * \fn          void checkChoice(gameData_t *gameData, int playerIndex)
 * \brief       Checks the player's choice.
 * \param       gameData : The game data structure.
 * \param       playerIndex : The index of the player.
 * \details     This function checks the player's choice against the secret code and updates the player's result in the game data.
 */
void checkChoice(gameData_t *gameData, int playerIndex) {
    LOG(1, "Checking player %d choice...\n", playerIndex);
    char colors[6] = "RBGCYM";
    int nbcolorsCombination[6] = {0};
    int nbcolorsPlayer[6] = {0};
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < 6; j++) {
            if (gameData->secretCode[i] == colors[j]) {
                nbcolorsCombination[j]++;
            }
            if (gameData->playerList.players[playerIndex].board[gameData->playerList.players[playerIndex].nbRound][i] == colors[j]) {
                nbcolorsPlayer[j]++;
            }
        }
        if (gameData->playerList.players[playerIndex].board[gameData->playerList.players[playerIndex].nbRound][i] == gameData->secretCode[i]) {
            gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][0]++;
            LOG(1, "Player %d color %c is at the right place.\n", playerIndex, gameData->playerList.players[playerIndex].board[gameData->playerList.players[playerIndex].nbRound][i]);
            LOG(1, "Player %d right place : %d.\n", playerIndex, gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][0]);
        }
    }
    for (int i = 0; i < 6; i++) {
        gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][1] += MIN(nbcolorsCombination[i], nbcolorsPlayer[i]);
        LOG(1, "Player %d right color : %d.\n", playerIndex, gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][1]);
    }
    gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][1] -= gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][0];
    if (gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][0] == BOARD_WIDTH && gameData->gameWinner == EMPTY) {
        gameData->gameWinner = playerIndex;
    }
    LOG(1, "Player %d choice checked.\n", playerIndex);
    LOG(1, "Player %d result : %d good place and %d good color.\n", playerIndex, gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][0], gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][1]);
}

/**
 * \fn          void endGame(gameData_t *gameData)
 * \brief       Ends the game.
 * \param       gameData : The game data structure.
 * \details     This function ends the game by determining the winner and sending the result to all players.
 */
void endGame(gameData_t *gameData) {
    LOG(1, "Ending game...\n");
    char buffer[10];
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i == gameData->gameWinner) {
            strcpy(buffer, "win\0");
        } else {
            sprintf(buffer, "loose:%d", gameData->gameWinner);
        }
        sendData(&gameData->playerList.players[i].socket, buffer, 6);
        sendData(&gameData->playerList.players[i].socket, gameData->secretCode, 7);
    }
    LOG(1, "Winner is player %d.\n", gameData->gameWinner);
    LOG(1, "Result sent. Game ended.\n");

}

/**
 * \fn          void *clientThreadHandler(void *args)
 * \brief       Handles the client threads.
 * \param       args : The arguments for the client thread handler.
 * \details     This function handles the player's game session. The player's choice is checked, and the result is sent to the player. The thread ends when the player has reached the maximum number of rounds or when the game has a winner.
 */
void *clientThreadHandler(void *args) {
    clientThreadHandlerArgs_t *clientThreadHandlerArgs = (clientThreadHandlerArgs_t *)args;
    while (clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound < MAX_ROUND && clientThreadHandlerArgs->gameData->gameWinner == EMPTY) {
        getPlayerChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        checkChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        sendResult(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound++;
    }
    LOG(1, "Ending thread for player %d.\n", clientThreadHandlerArgs->playerIndex);
    pthread_exit(NULL);
}



    