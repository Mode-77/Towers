/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    ---
*/

#include <vector>
#include <string>

#include "syntax_parser.h"

INPUT_TYPE parseInput(const std::vector<std::string>& input)
{
    /*
        If there are two tokens, then treat the input as valid syntax for a move.
        XXX XXXX

        If there is only one token in the input, then treat it as a command.
        XXXXXXX

        If there are no tokens, then this is empty input.

        If there are more than two tokens, then the input is invalid.
        XXX XXXX XX
    */
    switch(input.size()) {
    case 0: return EMPTY_INPUT;
    case 1: return COMMAND;
    case 2: return MOVE;
    default: return INVALID_INPUT;
    }
}

COMMAND_TYPE parseCommand(const std::vector<std::string>& input)
{
    std::string command(input.front());
    if(command == "quit") return REQUEST_QUIT;
    if(command == "reset") return REQUEST_RESET;
    if(command == "help") return REQUEST_HELP;
    return INVALID_COMMAND;
}
