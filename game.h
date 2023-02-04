/*
    Author: Jared Thomas
    Date:   Thursday, February 2, 2023

    This module contains the core game loop
*/

#ifndef GAME_H
#define GAME_H

/*
    Asks the player for the number of disks they want to play with.

    Blocks program flow until the player enters valid input, where valid input
    is a number between 1 and 8 inclusive.

    Returns the number of disks the player entered.
*/
unsigned askNumDisks();

/*
    Starts the game with an initial number of disks
*/
void game(unsigned initialDisks);

#endif
