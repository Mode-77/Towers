/*
    Author: Jared Thomas
    Date:   Tuesday, August 4, 2020
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "core_game.h"

int main(int argc, char* argv[])
{
    const int NUM_DISKS = (argc == 2) ? std::stoi(argv[1]) : 3;
    game(NUM_DISKS);
    return 0;
}
