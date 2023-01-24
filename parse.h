/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides string processing and parsing utilities.
*/

#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

// Retrieves input from the console and returns the result as a string
std::string getRawInput();

// Splits the string on the space (' ') character. Ignores leading spaces.
// Returns a vector containing the tokens.
std::vector<std::string> tokenize(const std::string& s);

enum PARSE_LONG_RESULT { INVALID_STRING, UNDERFLOW, OVERFLOW, SUCCESS };

// The input will not have leading or trailing spaces.
PARSE_LONG_RESULT parseLong(const char* s, long* result);

#endif
