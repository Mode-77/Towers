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
#include "parse.h"
#include "syntax_parser.h"
#include "move_parser.h"
#include "help.h"

static unsigned processInput(const std::vector<std::string>& tokens,
                             bool& requestQuit,
                             std::vector<Tower>& towers,
                             unsigned numDisks,
                             unsigned& moves,
                             std::string& status,
                             std::string& question);

static void moveState(const std::vector<std::string>& tokens,
                      bool& gameOver,
                      std::vector<Tower>& towers,
                      const TowerDrawer& towerDrawer,
                      unsigned numDisks,
                      unsigned& moves,
                      std::string& status,
                      std::string& question);

const unsigned GOAL_TOWER_VECTOR_INDEX = 2;

void game(unsigned numDisks)
{
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
        if(processInput(tokens, requestQuit, towers, numDisks, moves, status, question)) continue;
        moveState(tokens, gameOver, towers, towerDrawer, numDisks, moves, status, question);
    }
}

/*
    Calculates and returns the game score as the number of moves the player made
    out of the minimum moves required to win

    Returns 0 if valid input was gathered successfully, and flow can move into
    the move state.

    Returns 1 if the flow should return to the beginning of the game loop.
*/
static unsigned processInput(const std::vector<std::string>& tokens,
                             bool& requestQuit,
                             std::vector<Tower>& towers,
                             unsigned numDisks,
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
            switch(parseCommand(tokens)) {
            case REQUEST_QUIT:
                {
                    requestQuit = true;
                    return 1;
                }
            case REQUEST_RESET:
                {
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

*/
static void moveState(const std::vector<std::string>& tokens,
                      bool& gameOver,
                      std::vector<Tower>& towers,
                      const TowerDrawer& towerDrawer,
                      unsigned numDisks,
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
