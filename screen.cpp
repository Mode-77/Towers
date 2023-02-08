/*
    Author: Jared Thomas
    Date:   Sunday, January 29, 2023

    This module provides the platform-dependent clear screen command.
*/

#include "screen.h"

#ifdef PLATFORM_LINUX
    #include <iostream>
#endif

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif

void clearScreen()
{
#ifdef PLATFORM_LINUX
    std::cout << "\033[2J";
    std::cout << "\033[1;1H";
#endif

#ifdef PLATFORM_WINDOWS
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
#endif
}
