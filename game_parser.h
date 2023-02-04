/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    This module provides game-specific parsing functions.
*/

#ifndef GAME_PARSER_H
#define GAME_PARSER_H

#include <vector>
#include <string>

#include "Tower.h"

enum INPUT_TYPE { INVALID_INPUT, MOVE, COMMAND, EMPTY_INPUT };

/*
    Low-level parser that returns the type of input the tokens represent.

    If the input is a towers move, MOVE is returned.
    If the input is a game command, COMMAND is returned.
    If the input is an empty string, EMPTY_INPUT is returned.
    If the input was none of the above, INVALID_INPUT is returned.
*/
INPUT_TYPE parseInput(const std::vector<std::string>& tokens);

enum COMMAND_TYPE { REQUEST_QUIT, REQUEST_RESET, INVALID_COMMAND, REQUEST_HELP };

/*
    Mid-level parser that accepts a command string, and returns the requested
    operation
*/
COMMAND_TYPE parseCommand(const std::string& command);

enum MOVE_TYPE { VALID_MOVE, DISKLESS_TOWER, LARGER_ON_SMALLER, INVALID_MOVE_SYNTAX };

struct TOWER_MOVE {
    long int from;
    long int to;
    enum MOVE_TYPE moveType;
};

/*
    High-level parser that accepts a string representing a tower move and a vector
    of towers the moves should be done on.

    Returns a tower move record which contains information about the resulting move.
    The record can be later executed if the move is valid.

    If the semantics of the input are bad (negative or out-of-range tower number, etc.),
    then the returned record will have INVALID_MOVE_SYNTAX as a move type, and the
    from-to fields will be 0.

    If the input string would attempt to take a disk from a rod with no disks,
    then the returned record will have DISKLESS_TOWER as a move type, and the
    from-to fields will be populated with the appropriate tower indices (zero-indexed).

    If the input string would attempt to place a larger disk on top of a smaller disk,
    then the returned record will have LARGER_ON_SMALLER as a move type, and the
    from-to fields will be populated with the appropriate tower indices (zero-indexed).

    If none of the above cases occurred,
    then the returned record will have VALID_MOVE as a move type, and the
    from-to fields will be populated with the appropriate tower indices (zero-indexed).

*/
TOWER_MOVE parseMove(const std::vector<std::string>& tokens, const std::vector<Tower>& towers);

/*
    Executes a tower move record on the input vector of towers.

    The move type must not be INVALID_MOVE_SYNTAX or DISKLESS_TOWER.

    Move type LARGER_ON_SMALLER is allowed, but violates the traditional rules
    of the game.
*/
void doMove(TOWER_MOVE move, std::vector<Tower>& towers);

#endif
