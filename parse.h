/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides general-purpose string processing and parsing utilities.
*/

#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

/*
    Retrieves input from the console and returns the result as a string.

    Blocks program flow until a newline character is encountered.
*/
std::string getRawInput();

/*
    Splits the string on the space (' ') character, ignoring any leading and
    trailing spaces.

    Returns a vector containing the tokens.
*/
std::vector<std::string> tokenize(const std::string& s);

enum PARSE_LONG_RESULT { INVALID_STRING, UNDERFLOW, OVERFLOW, SUCCESS };

/*
    Attempts to interpret the input string as a base 10 integer. If successful,
    the interpreted value is stored at the location pointed to by result.

    The input should not have leading or trailing spaces.

    If the conversion was successful, SUCCESS is returned.

    If the conversion was successful and the interpreted value would be smaller
    than the minimum value for a (long), UNDERFLOW is returned.

    If the conversion was successful and the interpreted value would be larger
    than the maximum value for a (long), OVERFLOW is returned.

    If the string could not interpreted as a base-10 integer, INVALID_STRING
    is returned.
*/
PARSE_LONG_RESULT parseLong(const char* s, long* result);

#endif
