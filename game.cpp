/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    ---
*/

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

#include "Tower.h"
#include "TowerDrawer.h"
#include "screen.h"
#include "parse.h"

unsigned leastPossible(unsigned numDisks)
{
    return (1U << numDisks) - 1;
}

unsigned getScore(unsigned numDisks, unsigned moves)
{
    return (unsigned)(round(100.0 * leastPossible(numDisks) / moves));
}

void printResults(unsigned numDisks, unsigned moves)
{
    std::cout << "You finished in " << moves << " moves\n";

    std::cout << "Best possible is "\
        << leastPossible(numDisks) << " moves\n";

    std::cout << "Your score: " << getScore(numDisks, moves) << "%";
}

void drawTowers(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer)
{
    clearScreen();
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

bool checkForGameWon(const Tower& goalTower, unsigned totalDisks)
{
    return goalTower.num_disks() == totalDisks;
}

void resetTowers(std::vector<Tower>& towers, unsigned totalDisks)
{
    towers.clear();
    towers.push_back(Tower(totalDisks));
    towers.push_back(Tower());
    towers.push_back(Tower());
}

void resetGame(std::vector<Tower>& towers, unsigned numDisks, unsigned& moves, std::string& statusMessage, std::string& prompt)
{
    resetTowers(towers, numDisks);
    moves = 0;
    statusMessage = "Type \"help\" at any time for instructions. Good luck!";
    prompt = "What's your first move? ";
}

bool askPlayAgain()
{
    std::string input;
    do {
        std::cout << "Do you want to play again? (y/n): ";
        input = getRawInput();
    } while(!(input == "y" || input == "n"));
    return input == "y";
}

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
