/**
 *	\file		client.c
 *	\brief		Handles the main game loop for the client.
 *
 *	\details	This file contains the main game loop and the functions for checking if the game is over and ending the game.
 */
#include "client.h"

/**
 *	\fn			int main()
 *	\brief		The main game loop.
 *	\details    Shows the menu, initializes the game, connects to the server, and then enters the main game loop. The main game loop consists of sending the player's combination to the server, receiving the result of the combination, fetching the data of the other players, and showing the game state. The loop continues until the game is over.    
 */
int main() {
    game_t game;
    showMenu();
    initGame(&game);
    connexionWithServer(&game);
    showGame(game); 

    while (!isGameOver(game)){
        sendCombination(&game);
        getResult(&game);
        fetchOtherClientsData(&game);
        showGame(game); //show game
        game.nbRound++;
    }
    endGame(game); //end game

    return 0;
}

/**
 *	\fn			int isGameOver(game_t game)
 *	\brief		Checks if the game is over.
 *	\param 		game : The game state.
 *	\details		Returns 1 if the game is over (either the player has found the secret combination, the maximum number of rounds has been reached, or another player has found the secret combination), and 0 otherwise.
 */
int isGameOver(game_t game) {
    if (game.result[game.nbRound - 1][0] == BOARD_WIDTH) {
        return 1;
    } else if (game.nbRound == MAX_ROUND) {
        return 1;
    } else {
        for (int i = 0; i < game.nbPlayers - 1; i++) {
            if (game.otherPlayers[i].nbGoodPlace == BOARD_WIDTH) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 *	\fn			void endGame(game_t game)
 *	\brief		Ends the game.
 *	\param 		game : The game state.
 *	\details	Displays a message indicating whether the player has won or lost, who the winner is (if there is one), and what the secret combination was.
 */
void endGame(game_t game) {
    char buffer[10];
    int winner = EMPTY;
    if (game.nbRound == MAX_ROUND) {
        printf("Waiting for other players to finish the game...\n");
    }
    printf("Waiting for other players to finish their round...\n");
    receiveData(&(game.socket), buffer, 6);
    if (strcmp(buffer, "win") == 0) {
        printf("Congratulations! You won the game!\n");
    } else {
        sscanf(buffer, "loose:%d", &winner);
        if (winner == EMPTY) {
            printf("Sorry, you lost the game. Nobody found the secret combination.\n");
        } else {
            printf("Sorry, you lost the game. The winner is player %d.\n", winner+1);
        }
    }
    receiveData(&(game.socket), buffer, 7);
    printf("The secret combination was %s.\n", buffer);
}



