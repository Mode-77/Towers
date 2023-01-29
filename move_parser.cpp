/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides higher-order parsing for Towers moves.
*/

#include <vector>
#include <string>

#include "move_parser.h"
#include "parse.h"
#include "Tower.h"

TOWER_MOVE parseMove(const std::vector<std::string>& tokens, const std::vector<Tower>& towers)
{
    long int from, to;
    PARSE_LONG_RESULT fromResult = parseLong(tokens.at(0).c_str(), &from);
    PARSE_LONG_RESULT toResult = parseLong(tokens.at(1).c_str(), &to);

    // Return this when processing the move would result in a fatal error.
    const TOWER_MOVE PROBLEM_MOVE = { 0, 0, INVALID_MOVE_SYNTAX };

    if(!(fromResult == SUCCESS && toResult == SUCCESS)) {
        return PROBLEM_MOVE;
    }
    if((from < 1) || (from > 3)) {
        return PROBLEM_MOVE;
    }
    if((to < 1) || (to > 3)) {
        return PROBLEM_MOVE;
    }

    from--;
    to--;
    const Tower& towerFrom = towers.at(from);
    const Tower& towerTo = towers.at(to);
    if(towerFrom.is_diskless()) {
        TOWER_MOVE result = { from, to, DISKLESS_TOWER };
        return result;
    }
    if(!towerTo.is_diskless() &&
        (towerFrom.size_of_top() > towerTo.size_of_top())) {

        TOWER_MOVE result = { from, to, LARGER_ON_SMALLER };
        return result;
    }

    TOWER_MOVE result = { from, to, VALID_MOVE };
    return result;
}

void doMove(const TOWER_MOVE move, std::vector<Tower>& towers)
{
    Tower& towerFrom = towers.at(move.from);
    Tower& towerTo = towers.at(move.to);
    towerFrom.top_to_top(towerTo);
}
