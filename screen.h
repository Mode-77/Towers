/*
    Author: Jared Thomas
    Date:   Sunday, January 29, 2023

    This module provides the platform-dependent clear screen command.
*/

#ifndef SCREEN_H
#define SCREEN_H

// Clears the terminal.
//
// The actual system call used is platform-dependent.
void clearScreen();

#endif
