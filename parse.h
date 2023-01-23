/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides string processing and parsing utilities.
*/

#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

std::vector<std::string> tokenize(const std::string& s);

enum PARSE_LONG_RESULT { INVALID_STRING, UNDERFLOW, OVERFLOW, SUCCESS };

PARSE_LONG_RESULT parseLong(const char* s, long* result);

#endif
