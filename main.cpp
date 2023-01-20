#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "defines.h"

#include "Tower.h"
#include "TowerDrawer.h"



unsigned least_possible(size_t num_disks)
{
    return pow(2, num_disks) - 1;
}


double get_score(size_t num_disks, unsigned moves)
{
    return round(100.0 * least_possible(num_disks) / moves);
}


void printResults(size_t num_disks, unsigned moves)
{
    std::cout << "You finished in " << moves << " moves\n";

    std::cout << "Best possible is "\
        << least_possible(num_disks) << " moves\n";

    std::cout << "Your score: " << get_score(num_disks, moves) << "%\n";
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
    getline(std::cin, input);
    return input;
}


// 0 = Input is correct move syntax
// 1 = Input is empty
// 2 = Input is "quit"
// 3 = Input is "reset"
enum RESULT { SYNTAX_CORRECT, EMPTY_INPUT, REQUEST_QUIT, VALID_MOVE, DISKLESS_TOWER, LARGER_ON_SMALLER, REQUEST_RESET };

RESULT processInput(const std::string& input)
{
    if(input.empty()) return EMPTY_INPUT;
    if(!input.compare("quit")) return REQUEST_QUIT;
    if(!input.compare("reset")) return REQUEST_RESET;
    return SYNTAX_CORRECT;
}


// 0 = Input is a valid move
// 1 = Taking from a diskless tower
// 2 = Putting a larger disk on a smaller disk
RESULT checkForValidMove(const std::string& input, const std::vector<Tower>& towers)
{
    int from = stoi(input.substr(0, 1)) - 1;
    int to = stoi(input.substr(2, 1)) - 1;
    const Tower& towerFrom = towers.at(from);
    const Tower& towerTo = towers.at(to);
    if(towerFrom.is_diskless()) return DISKLESS_TOWER;
    if(!towerTo.is_diskless() &&
        (towerFrom.size_of_top() > towerTo.size_of_top())) return LARGER_ON_SMALLER;
    return VALID_MOVE;
}


void doMove(const std::string& move, std::vector<Tower>& towers)
{
    int from = stoi(move.substr(0, 1)) - 1;
    int to = stoi(move.substr(2, 1)) - 1;
    Tower& towerFrom = towers.at(from);
    Tower& towerTo = towers.at(to);
    towerFrom.top_to_top(towerTo);
}


bool checkForGameWon(const Tower& goalTower, int totalDisks)
{
    return goalTower.num_disks() == totalDisks;
}




int main(int argc, char* argv[])
{
    const int NUM_DISKS = (argc == 2) ? std::stoi(argv[1]) : 3;

    std::vector<Tower> towers;
    towers.push_back(Tower(NUM_DISKS));
    towers.push_back(Tower());
    towers.push_back(Tower());

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

        switch(processInput(rawInput)) {
        case SYNTAX_CORRECT: break;
        case EMPTY_INPUT: continue;
        case REQUEST_QUIT:
            {
                requestQuit = true;
                continue;
            }
        case REQUEST_RESET:
            {
                towers.clear();
                towers.push_back(Tower(NUM_DISKS));
                towers.push_back(Tower());
                towers.push_back(Tower());
                moves = 0;
                status = "Good luck!";
                question = "What's your first move? ";
                continue;
            }
        }

        switch(checkForValidMove(rawInput, towers)) {
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
