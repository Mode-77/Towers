/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    ---
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "Tower.h"
#include "TowerDrawer.h"

/*
    Returns the least possible number of moves required to win a game (perfect game).
    This is (2^d - 1), where d is the number of disks.
*/
unsigned leastPossible(unsigned numDisks);

/*
    Calculates and returns the game score as the number of moves the player made
    out of the minimum moves required to win
*/
unsigned getScore(unsigned numDisks, unsigned moves);

/*
    Prints the player's game statistics after the game has been won.
    The statistics are the number of moves made, minimum moves required,
    and the final score
*/
void printResults(unsigned numDisks, unsigned moves);

/*
    Clears the screen and draws the towers vector using a tower drawer
*/
void drawTowers(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer);

/*
    Prints the status message after drawing the towers
*/
void printStatus(const std::string& statusMessage);

/*

*/
void askQuestion(const std::string& question);

/*
    Returns true if the winning condition has been reached, returns false
    otherwise
*/
bool checkForGameWon(const Tower& goalTower, unsigned totalDisks);

/*
    Puts the towers back in their initial state
*/
void resetTowers(std::vector<Tower>& towers, unsigned totalDisks);

/*
    Puts the entire game back in its initial state; this includes resetting the
    towers and all state variables
*/
void resetGame(std::vector<Tower>& towers, unsigned numDisks, unsigned& moves, std::string& statusMessage, std::string& prompt);

/*
    Asks the player if they want to play again. Blocks program flow until the
    player enters valid input.

    Returns true if the player requests to play again, returns false if they
    don't.
*/
bool askPlayAgain();

/*
    Asks the player for the number of disks they want to play with.

    Blocks program flow until the player enters valid input.

    Returns the number of disks the player entered.
*/
unsigned askNumDisks();

#endif
