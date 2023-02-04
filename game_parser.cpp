/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    This module provides game-specific parsing functions.
*/

#include <vector>
#include <string>

#include "game_parser.h"
#include "parse.h"
#include "Tower.h"

INPUT_TYPE parseInput(const std::vector<std::string>& input)
{
    // If there are two tokens, then treat the input as valid syntax for a move.
    // XXX XXXX

    // If there is only one token in the input, then treat it as a command.
    // XXXXXXX

    // If there are no tokens, then this is empty input.

    // If there are more than two tokens, then the input is invalid.
    // XXX XXXX XX
    switch(input.size()) {
    case 0: return EMPTY_INPUT;
    case 1: return COMMAND;
    case 2: return MOVE;
    default: return INVALID_INPUT;
    }
}

COMMAND_TYPE parseCommand(const std::string& command)
{
    if(command == "quit") return REQUEST_QUIT;
    if(command == "reset") return REQUEST_RESET;
    if(command == "help") return REQUEST_HELP;
    return INVALID_COMMAND;
}

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
