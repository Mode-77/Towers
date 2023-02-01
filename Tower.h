#ifndef TOWER_H
#define TOWER_H

#include "Disk.h"
#include <vector>

#include <cstdlib>

class Tower {
public:
    /*
        Constructs a tower with no disks (diskless)
    */
    Tower();

    /*
        Constructs a tower with an initial number of disks.

        The disks will be stacked in increasing order from top to bottom.
    */
    Tower(unsigned num_disks);

    /*
        Returns the number of disks on the tower
    */
    unsigned num_disks() const;

    /*
        Returns the size of the topmost disk on the tower
    */
    unsigned size_of_top() const;

    /*
        Returns the size of the largest disk on the tower
    */
    unsigned size_of_largest_disk() const;

    /*
        Returns the size of a disk at a specific location on the tower.

        0 is the bottom of the tower.
    */
    unsigned size_of_disk_at(unsigned index) const;

    /*
        Returns true if the tower has no disks on it, returns false otherwise
    */
    bool is_diskless() const;

    /*

    */
    bool are_strictly_decreasing() const;

    /*
        Returns a reference to a specific disk on the tower
    */
    const Disk& disk_at(unsigned index) const;

    /*
        Moves the topmost disk from this tower to another tower
    */
    void top_to_top(Tower& dest_tower);

    /*

    */
    bool compare(const Tower&) const;

private:
    std::vector<Disk> disks_;
};

/*
    Returns the number of disks on the tower with the most disks in the vector
*/
unsigned highestTower(const std::vector<Tower>& towers);

#endif
