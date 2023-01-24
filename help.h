/*
    Author: Jared Thomas
    Date:   Monday, January 23, 2023

    This module provides the help command handler.
*/

#ifndef HELP_H
#define HELP_H

#include <vector>

#include "Tower.h"
#include "TowerDrawer.h"

// Clears the terminal and prints the help text explaining the rules and goal
// of the game.
//
// The passed in towers will be shown as a demonstration in the help text.
void showHelpText(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer);

void showCommandsHelp();

#endif
