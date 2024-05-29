/**
 *	\file		clientShow.c
 *	\brief		Handles the display of the game state for the client.
 *
 *	\details	This file contains the functions necessary for displaying the game state on the client side.
 */
#ifndef SHOW_H
#define SHOW_H

#include "clientData.h" 
#include <stdio.h> 


#define ANSI_RESET_ALL          "\x1b[0m"

#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"

#define ANSI_STYLE_BOLD         "\x1b[1m"
#define ANSI_STYLE_ITALIC       "\x1b[3m"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m"

/**
 *	\fn			void showMenu()
 *	\brief		Displays the game menu.
 *	\details	The game menu is printed to the console.
 */
void showMenu();

/**
 *	\fn			void showGame(game_t game)
 *	\brief		Displays the current game state.
 *	\param 		game : The game state to be displayed.
 *  \details	The game state is printed to the console with the appropriate format.
 */
void showGame(game_t game);

/**
 *	\fn			void showChar(char c)
 *	\brief		Displays a character with the appropriate format.
 *	\param 		c : The character to be displayed.
 *	\details	The character is printed to the console with the appropriate format.
 */
void showChar(char c);

#endif