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
    char inputChar;
    do {
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> inputChar;
    } while(!(inputChar == 'y' || inputChar == 'n'));
    return inputChar == 'y';
}
