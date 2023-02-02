/*
    Author: Jared Thomas
    Date:   Tuesday, August 4, 2020
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "game.h"
#include "screen.h"
#include "parse.h"
#include "syntax_parser.h"
#include "move_parser.h"
#include "help.h"
#include "Tower.h"
#include "TowerDrawer.h"

enum COMMAND_TYPE { REQUEST_QUIT, REQUEST_RESET, INVALID_COMMAND, REQUEST_HELP };

COMMAND_TYPE parseCommand(const std::vector<std::string>& input)
{
    std::string command(input.front());
    if(command == "quit") return REQUEST_QUIT;
    if(command == "reset") return REQUEST_RESET;
    if(command == "help") return REQUEST_HELP;
    return INVALID_COMMAND;
}

int main(int argc, char* argv[])
{
    const int NUM_DISKS = (argc == 2) ? std::stoi(argv[1]) : 3;
    const unsigned NUM_TUTORIAL_DISKS = 3;
    const unsigned TUTORIAL_ROD_HEIGHT = NUM_TUTORIAL_DISKS + 2;
    const unsigned GOAL_TOWER_VECTOR_INDEX = 2;

    std::vector<Tower> towers;          // Actual game rods
    TowerDrawer tower_drawer(NUM_DISKS + 3);
    resetTowers(towers, NUM_DISKS);

    std::vector<Tower> tutorialTowers;  // Appears on the help text
    TowerDrawer tutorialTowerDrawer(TUTORIAL_ROD_HEIGHT);
    resetTowers(tutorialTowers, NUM_TUTORIAL_DISKS);

    unsigned moves = 0;
    bool requestQuit = false;
    bool gameOver = false;
    std::string status, question, rawInput;
    status = "Type \"help\" at any time for instructions. Good luck!";
    question = "What's your first move? ";
    while(!(requestQuit || gameOver)) {
        drawTowers(towers, tower_drawer);
        printStatus(status);
        askQuestion(question);
        std::string rawInput = getRawInput();
        std::vector<std::string> tokens = tokenize(rawInput);

        switch(parseInput(tokens)) {
        case MOVE: break;
        case EMPTY_INPUT: continue;
        case COMMAND:
            {
                switch(parseCommand(tokens)) {
                case REQUEST_QUIT:
                    {
                        requestQuit = true;
                        continue;
                    }
                case REQUEST_RESET:
                    {
                        resetGame(towers, NUM_DISKS, moves, status, question);
                        continue;
                    }
                case REQUEST_HELP:
                    {
                        clearScreen();
                        showHelpText(tutorialTowers, tutorialTowerDrawer);
                        std::cout << "\n\n";
                        std::cout << "Press \"Enter\" for the list of commands...";
                        getRawInput();
                        clearScreen();
                        showCommandsHelp();
                        std::cout << "\n\n";
                        std::cout << "Press \"Enter\" to go back to the game...";
                        getRawInput();
                        continue;
                    }
                case INVALID_COMMAND:
                    {
                        status = "No such command...";
                        continue;
                    }
                }
            }
        case INVALID_INPUT:
            {
                status = "Huh?";
                continue;
            }
        }

        TOWER_MOVE towerMove = parseMove(tokens, towers);
        switch(towerMove.moveType) {
        case VALID_MOVE:
            {
                doMove(towerMove, towers);
                moves++;
                if(checkForGameWon(towers.at(GOAL_TOWER_VECTOR_INDEX), NUM_DISKS)) {
                    drawTowers(towers, tower_drawer);
                    printStatus("You win!");
                    printResults(NUM_DISKS, moves);
                    std::cout << "\n\n";
                    gameOver = !askPlayAgain();
                    if(!gameOver) {
                        resetGame(towers, NUM_DISKS, moves, status, question);
                    }
                    continue;
                }
                status = "";
                question = "What's your next move? ";
                break;
            }
        case DISKLESS_TOWER:
            {
                status = "Nothing on that tower...";
                break;
            }
        case LARGER_ON_SMALLER:
            {
                status = "Can't place a larger disk on a smaller disk...";
                break;
            }
        case INVALID_MOVE_SYNTAX:
            {
                status = "Can't do that...";
                break;
            }
        }
    }

    return 0;
}
