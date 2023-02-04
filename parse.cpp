/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023

    This module provides general-purpose string processing and parsing utilities.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <climits>
#include "parse.h"

std::string getRawInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::vector<std::string> tokenize(const std::string& s)
{
    // Create an intermediate string buffer
    const std::size_t BUFFER_LENGTH = s.length() + 1;
    char* buffer = new char[BUFFER_LENGTH];
    memset(buffer, 0, BUFFER_LENGTH);
    // Copy the string into the buffer
    s.copy(buffer, s.length());
    // Tokenize
    std::vector<std::string> result;
    char* token = strtok(buffer, " ");
    while(token) {
        result.push_back(std::string(token));
        token = strtok(nullptr, " ");
    }
    delete[] buffer;
    return result;
}

PARSE_LONG_RESULT parseLong(const char* s, long* result)
{
    const char* afterTheNumber = s + strlen(s);
    char* endPtr = nullptr;
    int previousErrno = errno;
    errno = 0;

    long int longValue = strtol(s, &endPtr, 10);

    if(endPtr != afterTheNumber) {
        errno = previousErrno;
        return INVALID_STRING;
    }
    if(longValue == LONG_MIN && errno == ERANGE) {
        errno = previousErrno;
        return UNDERFLOW;
    }
    if(longValue == LONG_MAX && errno == ERANGE) {
        errno = previousErrno;
        return OVERFLOW;
    }

    errno = previousErrno;
    *result = longValue;
    return SUCCESS;
}
