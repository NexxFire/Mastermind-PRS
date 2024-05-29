/**
 *	\file		clientInit.c
 *	\brief		Initializes the game state for the client.
 *
 *	\details	This file contains the functions necessary for initializing the game state on the client side.
 */
#include "clientInit.h" // client/include/init.h


/**
 *	\fn			void _initBoard(char board[MAX_ROUND][BOARD_WIDTH])
 *	\brief		Initializes the game board.
 *	\param 		board : The game board to be initialized.
 *  \details    The game board is filled with the EMPTY constant.
 */
void _initBoard(char board[MAX_ROUND][BOARD_WIDTH]) {
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }
}

/**
 *	\fn			void _initResult(char result[MAX_ROUND][RESULT_WIDTH])
 *	\brief		Initializes the result array.
 *	\param 		result : The result array to be initialized.
 *	\details	The result array is filled with the EMPTY_SCORE constant.
 */
void _initResult(char result[MAX_ROUND][RESULT_WIDTH]) {
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < RESULT_WIDTH; j++) {
            result[i][j] = EMPTY_SCORE;
        }
    }
}

/**
 *	\fn			void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS-1])
 *	\brief		Initializes the array of other players.
 *	\param 		otherPlayers : The array of other players to be initialized.
 *	\details	The number of rounds, good places, and good colors for each other player is set to 0.
 */
void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS-1]) {
    for (int i = 0; i < MAX_PLAYERS-1; i++) {
        otherPlayers[i].nbRound = 0;
        otherPlayers[i].nbGoodPlace = 0;
        otherPlayers[i].nbGoodColor = 0;
    }
}


/**
 *	\fn			void initGame(game_t *game)
 *	\brief		Initializes the game state.
 *	\param 		game : The game state to be initialized.
 *	\details	The number of players and rounds in the game state is set to 0, and the game board, result array, and other players array are initialized.
 */
void initGame(game_t *game) {
    game->nbPlayers = 0;
    game->nbRound = 0;
    _initBoard(game->board);
    _initResult(game->result);
    _initOtherPlayers(game->otherPlayers);
}