#pragma once

#include "Tower.h"


struct PerfectHanoi {
    PerfectHanoi(size_t num_disks);
    void do_next_move();
    bool compare(const TowerList&) const;

private:
    void do_valid_action(Tower& X, Tower& Y) const;


    TowerList towers;
    const size_t starting_num_disks;
    const int odd_num_disks;
    int thinker;


    const int best_moves[2][3][2] =
    {
        {
            { 0, 1 },
        { 0, 2 },
        { 1, 2 }
        },

    {
        { 0, 2 },
        { 0, 1 },
        { 1, 2 }
    }
    };
};
