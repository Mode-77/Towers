#include <vector>
#include <string>

#include "move_parser.h"
#include "parse.h"
#include "Tower.h"

// 0 = Input is a valid move
// 1 = Taking from a diskless tower
// 2 = Putting a larger disk on a smaller disk
TOWER_MOVE parseMove(const std::vector<std::string>& input, const std::vector<Tower>& towers)
{
    long int from, to;
    PARSE_LONG_RESULT fromResult = parseLong(input.at(0).c_str(), &from);
    PARSE_LONG_RESULT toResult = parseLong(input.at(1).c_str(), &to);
    if(!(fromResult == SUCCESS && toResult == SUCCESS)) {
        TOWER_MOVE result = { 0, 0, INVALID_MOVE_SYNTAX };
        return result;
    }
    if((from < 1) || (from > 3)) {
        TOWER_MOVE result = { 0, 0, INVALID_MOVE_SYNTAX };
        return result;
    }
    if((to < 1) || (to > 3)) {
        TOWER_MOVE result = { 0, 0, INVALID_MOVE_SYNTAX };
        return result;
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
