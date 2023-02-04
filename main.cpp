/*
    Author: Jared Thomas
    Date:   Tuesday, August 4, 2020
*/

#include "game.h"
#include "core_game.h"
#include "screen.h"

int main()
{
    clearScreen();
    game(askNumDisks());
    return 0;
}
