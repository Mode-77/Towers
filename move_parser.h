/*
    Author: Jared Thomas
    Date:   Sunday, January 22, 2023
*/

#ifndef MOVE_PARSER_H
#define MOVE_PARSER_H

#include <vector>
#include <string>

#include "Tower.h"

enum MOVE_TYPE { VALID_MOVE, DISKLESS_TOWER, LARGER_ON_SMALLER, INVALID_MOVE_SYNTAX };

struct TOWER_MOVE {
    long int from;
    long int to;
    enum MOVE_TYPE moveType;
};

TOWER_MOVE parseMove(const std::vector<std::string>& input, const std::vector<Tower>& towers);

void doMove(const TOWER_MOVE move, std::vector<Tower>& towers);

#endif
