/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides higher-order parsing for Towers moves.
*/

#ifndef MOVE_PARSER_H
#define MOVE_PARSER_H

#include <vector>
#include <string>

#include "Tower.h"

/*
    DISKLESS_TOWER - Attempt to take a disk from a rod with no disks.
    LARGER_ON_SMALLER - Attempt to place a larger disk on a smaller disk.
    INVALID_MOVE_SYNTAX - The input could not be processed due to one or more
    of the following reasons:
        1. Some input couldn't be converted to a numerical type
        2. Some numerical identifier would be out of range
*/
enum MOVE_TYPE { VALID_MOVE, DISKLESS_TOWER, LARGER_ON_SMALLER, INVALID_MOVE_SYNTAX };

struct TOWER_MOVE {
    long int from;
    long int to;
    enum MOVE_TYPE moveType;
};

/*
    Parses tokens and produces a tower move record.
*/
TOWER_MOVE parseMove(const std::vector<std::string>& tokens, const std::vector<Tower>& towers);

/*
    Executes the towers move.

    The move type must not be INVALID_MOVE_SYNTAX or DISKLESS_TOWER.

    Move type LARGER_ON_SMALLER is allowed, but violates the traditional rules
    of the game.
*/
void doMove(TOWER_MOVE move, std::vector<Tower>& towers);

#endif
