/*
    Author: Jared Thomas
    Date:   Wednesday, February 1, 2023

    ---
*/

#ifndef SYNTAX_PARSER_H
#define SYNTAX_PARSER_H

#include <vector>
#include <string>

/*

*/
enum INPUT_TYPE { INVALID_INPUT, MOVE, COMMAND, EMPTY_INPUT };

/*

*/
enum COMMAND_TYPE { REQUEST_QUIT, REQUEST_RESET, INVALID_COMMAND, REQUEST_HELP };

/*

*/
INPUT_TYPE parseInput(const std::vector<std::string>& input);

/*

*/
COMMAND_TYPE parseCommand(const std::vector<std::string>& input);

#endif
