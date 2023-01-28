#pragma once

#include "Disk.h"
#include <vector>

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

size_t highestTower(const std::vector<Tower>& towers);
