#pragma once

#include "Disk.h"
#include "List.h"
#include <vector>

#include "unit_tests.h"

class Tower {
public:
    Tower();
    Tower(size_t num_disks);

    size_t num_disks() const;
    int size_of_top() const;
    int size_of_largest_disk() const;
    int size_of_disk_at(size_t place) const;
    bool is_diskless() const;
    bool are_strictly_decreasing() const;
    const Disk& disk_at(size_t index) const;
    void top_to_top(Tower& dest_tower);
    bool compare(const Tower&) const;

private:
    std::vector<Disk> disks_;
};



class TowerList: public List<Tower> {
public:
    size_t highest_tower() const;
    bool compare(const TowerList&) const;
};


struct PerfectHanoi {
    PerfectHanoi(size_t num_disks);
    void do_next_move();
    bool compare(const TowerList&) const;

private:
    //bool equals(const int* X, const int* Y) const;
    //void swap(int* X) const;
    //bool is_best_move(int* actual, const int* best) const;
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
