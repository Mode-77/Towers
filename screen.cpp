/*
    Author: Jared Thomas
    Date:   Sunday, January 29, 2023

    This module provides the platform-dependent clear screen command.
*/

#include "screen.h"

#ifdef PLATFORM_LINUX
    #define CLEAR_SCREEN_COMMAND    "clear"
#endif

#ifdef PLATFORM_WINDOWS
    #define CLEAR_SCREEN_COMMAND    "cls"
#endif

#include <cstdlib>

void clearScreen()
{
    system(CLEAR_SCREEN_COMMAND);
}
