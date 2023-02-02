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

/*
    Clears the screen and starts the help texts which come in two screens.

    The passed in towers will be shown as a demonstration in the explanation.
*/
void showHelpText(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer);

/*
    Shows part 1/2 of the help text which is the game objective, rules, and
    inputs explanation
*/
void showExpanation(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer);

/*
    Shows part 2/2 of the help text which is the list of game commands
*/
void showCommandsHelp();

#endif
