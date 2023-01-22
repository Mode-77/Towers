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


std::vector<std::string> tokenize(const std::string&);

// Returns the number of tokens in the input string
int numTokens(const std::string& s)
{
    return tokenize(s).size();
}


// Splits the string on the space (' ') character. Ignores leading spaces.
// Returns a vector containing the tokens.
std::vector<std::string> tokenize(const std::string& s)
{
    /* TODO: BROKEN */
    // Create an intermediate string buffer
    const std::size_t BUFFER_LENGTH = s.length() + 1;
    char* buffer = new char[BUFFER_LENGTH];
    memset(buffer, 0, BUFFER_LENGTH);
    // Copy the string into the buffer
    s.copy(buffer, s.length());
    // Tokenize
    std::vector<std::string> result;
    char* token = strtok(buffer, " ");
    while(token) {
        result.push_back(std::string(token));
        token = strtok(nullptr, " ");
    }
    delete[] buffer;
    return result;
}


enum INPUT_TYPE { INVALID_INPUT, MOVE, COMMAND, EMPTY_INPUT };

INPUT_TYPE parseInput(const std::string& input)
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
    int numberTokens = numTokens(input);
    if(numberTokens == 2) return MOVE;
    if(numberTokens == 1) return COMMAND;
    if(numberTokens == 0) return EMPTY_INPUT;
    return INVALID_INPUT;
}


enum COMMAND_TYPE { REQUEST_QUIT, REQUEST_RESET, INVALID_COMMAND };

COMMAND_TYPE parseCommand(const std::string& input)
{
    std::string command(tokenize(input).front());
    if(command == "quit") return REQUEST_QUIT;
    if(command == "reset") return REQUEST_RESET;
    return INVALID_COMMAND;
}


enum MOVE_TYPE { VALID_MOVE, DISKLESS_TOWER, LARGER_ON_SMALLER };

// 0 = Input is a valid move
// 1 = Taking from a diskless tower
// 2 = Putting a larger disk on a smaller disk
MOVE_TYPE parseMove(const std::string& input, const std::vector<Tower>& towers)
{
    std::vector<std::string> tokens(tokenize(input));
    int from = std::stoi(tokens.at(0)) - 1;
    int to = std::stoi(tokens.at(1)) - 1;
    const Tower& towerFrom = towers.at(from);
    const Tower& towerTo = towers.at(to);
    if(towerFrom.is_diskless()) return DISKLESS_TOWER;
    if(!towerTo.is_diskless() &&
        (towerFrom.size_of_top() > towerTo.size_of_top())) return LARGER_ON_SMALLER;
    return VALID_MOVE;
}


void doMove(const std::string& move, std::vector<Tower>& towers)
{
    std::vector<std::string> tokens(tokenize(move));
    int from = std::stoi(tokens.at(0)) - 1;
    int to = std::stoi(tokens.at(1)) - 1;
    Tower& towerFrom = towers.at(from);
    Tower& towerTo = towers.at(to);
    towerFrom.top_to_top(towerTo);
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
    status = "Good luck!";
    question = "What's your first move? ";
    while(!(requestQuit || won)) {
        drawTowers(towers, tower_drawer);
        printStatus(status);
        askQuestion(question);
        rawInput = getRawInput();

        switch(parseInput(rawInput)) {
        case MOVE: break;
        case EMPTY_INPUT: continue;
        case COMMAND:
            {
                switch(parseCommand(rawInput)) {
                case REQUEST_QUIT:
                    {
                        requestQuit = true;
                        continue;
                    }
                case REQUEST_RESET:
                    {
                        resetTowers(towers, NUM_DISKS);
                        moves = 0;
                        status = "Good luck!";
                        question = "What's your first move? ";
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

        switch(parseMove(rawInput, towers)) {
        case VALID_MOVE:
            {
                doMove(rawInput, towers);
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
        }
    }

    if(won) {
        drawTowers(towers, tower_drawer);
        printStatus("You win!");
        printResults(NUM_DISKS, moves);
    }

    return 0;
}
