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

#include "defines.h"

#include "parse.h"
#include "move_parser.h"
#include "Tower.h"
#include "TowerDrawer.h"



unsigned leastPossible(size_t num_disks)
{
    return pow(2, num_disks) - 1;
}


double getScore(size_t num_disks, unsigned moves)
{
    return round(100.0 * leastPossible(num_disks) / moves);
}


void printResults(size_t num_disks, unsigned moves)
{
    std::cout << "You finished in " << moves << " moves\n";

    std::cout << "Best possible is "\
        << leastPossible(num_disks) << " moves\n";

    std::cout << "Your score: " << getScore(num_disks, moves) << "%\n";
}


void drawTowers(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer)
{
    system("clear");
    towerDrawer.draw(towers);
}


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


std::string getRawInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}


enum INPUT_TYPE { INVALID_INPUT, MOVE, COMMAND, EMPTY_INPUT };

INPUT_TYPE parseInput(const std::vector<std::string>& input)
{
    /*
        If there are two tokens, then treat the input as valid syntax for a move.
        XXX XXXX

        If there is only one token in the input, then treat it as a command.
        XXXXXXX

        If there are no tokens, then this is empty input.

        If there are more than two tokens, then the input is invalid.
        XXX XXXX XX
    */
    switch(input.size()) {
    case 0: return EMPTY_INPUT;
    case 1: return COMMAND;
    case 2: return MOVE;
    default: return INVALID_INPUT;
    }
}


enum COMMAND_TYPE { REQUEST_QUIT, REQUEST_RESET, INVALID_COMMAND, REQUEST_HELP };

COMMAND_TYPE parseCommand(const std::vector<std::string>& input)
{
    std::string command(input.front());
    if(command == "quit") return REQUEST_QUIT;
    if(command == "reset") return REQUEST_RESET;
    if(command == "help") return REQUEST_HELP;
    return INVALID_COMMAND;
}


bool checkForGameWon(const Tower& goalTower, int totalDisks)
{
    return goalTower.num_disks() == totalDisks;
}


void resetTowers(std::vector<Tower>& towers, int totalDisks)
{
    towers.clear();
    towers.push_back(Tower(totalDisks));
    towers.push_back(Tower());
    towers.push_back(Tower());
}


int main(int argc, char* argv[])
{
    const int NUM_DISKS = (argc == 2) ? std::stoi(argv[1]) : 3;

    std::vector<Tower> towers;
    resetTowers(towers, NUM_DISKS);

    const int GOAL_TOWER_INDEX = 2;
    TowerDrawer tower_drawer(NUM_DISKS + 3);

    int moves = 0;
    bool requestQuit = false;
    bool won = false;
    std::string status, question, rawInput;
    status = "Type \"help\" at any time for instructions. Good luck!";
    question = "What's your first move? ";
    while(!(requestQuit || won)) {
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
                        resetTowers(towers, NUM_DISKS);
                        moves = 0;
                        status = "Type \"help\" at any time for instructions. Good luck!";
                        question = "What's your first move? ";
                        continue;
                    }
                case REQUEST_HELP:
                    {
                        system("clear");
                        std::cout << "The goal of Towers is to move all the disks from the leftmost rod to the rightmost rod.\n";
                        std::cout << "Sounds easy, right? But not so fast!\n";
                        std::cout << "You can only move the topmost disk from any tower.\n";
                        std::cout << "On top of that, you can't put a larger disk on top of a smaller one!\n";
                        std::cout << "\n";
                        tower_drawer.draw(towers);
                        std::cout << "\n";
                        std::cout << "To move a disk from one rod to another, type the rod number you want to\n";
                        std::cout << "move from, then the rod number to move to, separated by a space. Like this:\n";
                        std::cout << "\n";
                        std::cout << "1 2\n";
                        std::cout << "\n";
                        std::cout << "This would move the topmost disk from the left rod to the middle rod.\n";
                        std::cout << "If you can move all the disks to the leftmost rod, you win!\n";
                        std::cout << "\n";
                        std::cout << "Press \"Enter\" to go back...";
                        getRawInput();
                        continue;
                    }
                case INVALID_COMMAND:
                    {
                        status = "Unknown command";
                        continue;
                    }
                }
            }
        case INVALID_INPUT:
            {
                status = "Invalid input";
                continue;
            }
        }

        TOWER_MOVE towerMove = parseMove(tokens, towers);
        switch(towerMove.moveType) {
        case VALID_MOVE:
            {
                doMove(towerMove, towers);
                moves++;
                won = checkForGameWon(towers.at(GOAL_TOWER_INDEX), NUM_DISKS);
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

    if(won) {
        drawTowers(towers, tower_drawer);
        printStatus("You win!");
        printResults(NUM_DISKS, moves);
    }

    return 0;
}
