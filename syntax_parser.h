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
INPUT_TYPE parseInput(const std::vector<std::string>& input);

#endif
