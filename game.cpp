/*
    Author: Jared Thomas
    Date:   Thursday, February 2, 2023

    This module contains the core game loop
*/

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <cassert>

#include "Tower.h"
#include "TowerDrawer.h"
#include "screen.h"
#include "game.h"
#include "game_parser.h"
#include "parse.h"
#include "help.h"

static unsigned inputState(const std::vector<std::string>& tokens,
                           bool& requestQuit,
                           std::vector<Tower>& towers,
                           unsigned& numDisks,
                           unsigned& moves,
                           std::string& status,
                           std::string& question);

static void moveState(const std::vector<std::string>& tokens,
                      bool& gameOver,
                      std::vector<Tower>& towers,
                      const TowerDrawer& towerDrawer,
                      unsigned& numDisks,
                      unsigned& moves,
                      std::string& status,
                      std::string& question);

const unsigned GOAL_TOWER_VECTOR_INDEX = 2;

/*
    Returns the least possible number of moves required to win a game (perfect game).
    This is (2^d - 1), where d is the number of disks.
*/
unsigned leastPossible(unsigned numDisks)
{
    return (1U << numDisks) - 1;
}

/*
    Calculates and returns the game score as the number of moves the player made
    out of the minimum moves required to win
*/
unsigned getScore(unsigned numDisks, unsigned moves)
{
    return (unsigned)(round(100.0 * leastPossible(numDisks) / moves));
}

/*
    Prints the player's game statistics after the game has been won.
    The statistics are the number of moves made, minimum moves required,
    and the final score
*/
void printResults(unsigned numDisks, unsigned moves)
{
    std::cout << "You finished in " << moves << " moves\n";

    std::cout << "Best possible is "\
        << leastPossible(numDisks) << " moves\n";

    std::cout << "Your score: " << getScore(numDisks, moves) << "%";
}

/*
    Clears the screen and draws the towers vector using a tower drawer
*/
void drawTowers(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer)
{
    clearScreen();
    towerDrawer.draw(towers);
}

/*
    Prints the status message after drawing the towers
*/
void printStatus(const std::string& statusMessage)
{
    std::cout << "\n";
    std::cout << statusMessage << "\n";
    std::cout << "\n";
}


void askQuestion(const std::string& question)
{
    std::cout << question;
}

/*
    Returns true if the winning condition has been reached, returns false
    otherwise
*/
bool checkForGameWon(const Tower& goalTower, unsigned totalDisks)
{
    return goalTower.num_disks() == totalDisks;
}

/*
    Puts the towers back in their initial state
*/
void resetTowers(std::vector<Tower>& towers, unsigned totalDisks)
{
    towers.clear();
    towers.push_back(Tower(totalDisks));
    towers.push_back(Tower());
    towers.push_back(Tower());
}

/*
    Puts the entire game back in its initial state; this includes resetting the
    towers and all state variables
*/
void resetGame(std::vector<Tower>& towers, unsigned numDisks, unsigned& moves, std::string& statusMessage, std::string& prompt)
{
    resetTowers(towers, numDisks);
    moves = 0;
    statusMessage = "Type \"help\" at any time for instructions. Good luck!";
    prompt = "What's your first move? ";
}

/*
    Asks the player if they want to play again. Blocks program flow until the
    player enters valid input.

    Returns true if the player requests to play again, returns false if they
    don't.
*/
bool askPlayAgain()
{
    std::string input;
    do {
        std::cout << "Do you want to play again? (y/n): ";
        input = getRawInput();
    } while(!(input == "y" || input == "n"));
    return input == "y";
}

/*
    Asks the player for the number of disks they want to play with.

    Blocks program flow until the player enters valid input, where valid input
    is a number between 1 and 8 inclusive.

    Returns the number of disks the player entered.
*/
unsigned askNumDisks()
{
    std::string input;
    long numDisks;
    do {
        input.clear();
        numDisks = 0;
        do {
            std::cout << "How many disks do you want to play with? (1=Easiest, 8=Hardest): ";
            input = getRawInput();
        } while(parseLong(input.c_str(), &numDisks) != SUCCESS);
    } while((numDisks < 1) || (numDisks > 8));
    return (unsigned)numDisks;
}


void game(unsigned initialDisks)
{
    unsigned numDisks = initialDisks;

    std::vector<Tower> towers;  // Actual game rods
    resetTowers(towers, numDisks);

    TowerDrawer towerDrawer(numDisks + 3);

    unsigned moves = 0;
    bool requestQuit = false;
    bool gameOver = false;
    std::string status, question, rawInput;

    status = "Type \"help\" at any time for instructions. Good luck!";
    question = "What's your first move? ";
    while(!(requestQuit || gameOver)) {
        drawTowers(towers, towerDrawer);
        printStatus(status);
        askQuestion(question);
        std::string rawInput = getRawInput();
        std::vector<std::string> tokens = tokenize(rawInput);
        if(inputState(tokens, requestQuit, towers, numDisks, moves, status, question)) continue;
        moveState(tokens, gameOver, towers, towerDrawer, numDisks, moves, status, question);
    }
}

/*
    Performs input processing and command handling of tokens.

    Returns 0 if the input is a tower move and should be passed on to the move
    parser.

    Returns 1 if the flow should return to the beginning of the game loop.
*/
static unsigned inputState(const std::vector<std::string>& tokens,
                           bool& requestQuit,
                           std::vector<Tower>& towers,
                           unsigned& numDisks,
                           unsigned& moves,
                           std::string& status,
                           std::string& question)
{
    const unsigned NUM_TUTORIAL_DISKS = 3;
    const unsigned TUTORIAL_ROD_HEIGHT = NUM_TUTORIAL_DISKS + 2;

    std::vector<Tower> tutorialTowers;  // Appears on the help text
    TowerDrawer tutorialTowerDrawer(TUTORIAL_ROD_HEIGHT);
    resetTowers(tutorialTowers, NUM_TUTORIAL_DISKS);

    switch(parseInput(tokens)) {
    case MOVE: return 0;
    case EMPTY_INPUT: return 1;
    case COMMAND:
        {
            switch(parseCommand(tokens.front())) {
            case REQUEST_QUIT:
                {
                    requestQuit = true;
                    return 1;
                }
            case REQUEST_RESET:
                {
                    numDisks = askNumDisks();
                    resetGame(towers, numDisks, moves, status, question);
                    return 1;
                }
            case REQUEST_HELP:
                {
                    showHelpText(tutorialTowers, tutorialTowerDrawer);
                    return 1;
                }
            case INVALID_COMMAND:
                {
                    status = "No such command...";
                    return 1;
                }
            }
            break;  // This only pacifies the compiler; it cannot really be reached.
        }
    case INVALID_INPUT:
        {
            status = "Huh?";
            return 1;
        }
    }
    assert(0);  // Impossible to get here
    return 0;
}

/*
    Takes in tokens from the input stage and attempts to process them as tower
    moves.
*/
static void moveState(const std::vector<std::string>& tokens,
                      bool& gameOver,
                      std::vector<Tower>& towers,
                      const TowerDrawer& towerDrawer,
                      unsigned& numDisks,
                      unsigned& moves,
                      std::string& status,
                      std::string& question)
{
    TOWER_MOVE towerMove = parseMove(tokens, towers);
    switch(towerMove.moveType) {
    case VALID_MOVE:
        {
            doMove(towerMove, towers);
            moves++;
            if(checkForGameWon(towers.at(GOAL_TOWER_VECTOR_INDEX), numDisks)) {
                drawTowers(towers, towerDrawer);
                printStatus("You win!");
                printResults(numDisks, moves);
                std::cout << "\n\n";
                gameOver = !askPlayAgain();
                if(!gameOver) {
                    numDisks = askNumDisks();
                    resetGame(towers, numDisks, moves, status, question);
                }
                return;
            }
            status = "";
            question = "What's your next move? ";
            return;
        }
    case DISKLESS_TOWER:
        {
            status = "Nothing on that tower...";
            return;
        }
    case LARGER_ON_SMALLER:
        {
            status = "Can't place a larger disk on a smaller disk...";
            return;
        }
    case INVALID_MOVE_SYNTAX:
        {
            status = "Can't do that...";
        }
    }
}
