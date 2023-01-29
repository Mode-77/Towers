/*
    Author: Jared Thomas
    Date:   Monday, January 23, 2023

    This module provides the help command handler.
*/

#include "help.h"

#include <vector>
#include <cstdlib>
#include <iostream>

#include "Tower.h"
#include "TowerDrawer.h"

// Clears the terminal and prints the help text explaining the rules and goal
// of the game.
//
// The passed in towers will be shown as a demonstration in the help text.
void showHelpText(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer)
{
    std::cout << "Towers, an adaptation of the game \"Tower of Hanoi\"\n";
    std::cout << "Nexus Game Studios, 2023\n";
    std::cout << "Programming, Jared Thomas\n";
    std::cout << "\n";
    std::cout << "The goal of Towers is to move all the disks from the leftmost rod to the rightmost rod.\n";
    std::cout << "Sounds easy, right? But not so fast!\n";
    std::cout << "You can only move the topmost disk from any tower.\n";
    std::cout << "On top of that, you can't put a larger disk on top of a smaller one!\n";
    towerDrawer.draw(towers);
    std::cout << "\n";
    std::cout << "To move a disk from one rod to another, type the rod number you want to\n";
    std::cout << "move from, then the rod number to move to, separated by a space. Like this:\n";
    std::cout << "\n";
    std::cout << "1 2\n";
    std::cout << "\n";
    std::cout << "This would move the topmost disk from the left rod to the middle rod.\n";
    std::cout << "If you can move all the disks to the rightmost rod, you win!";
}

// Prints the commands help text.
void showCommandsHelp()
{
    std::cout << "Commands\n";
    std::cout << "\n";
    std::cout << "quit       Quit the game\n";
    std::cout << "help       Show the game explanation, rules, and commands\n";
    std::cout << "reset      Start the game over again";
}
