#include "Tower.h"
#include "Disk.h"
#include <cassert>
#include <climits>
#include <iostream>

Tower::Tower()
{

}


Tower::Tower(unsigned num_disks)
{
    while(num_disks > 0) {
        disks_.push_back(Disk(num_disks));
        num_disks--;
    }
}


unsigned Tower::num_disks() const
{
    // The cast is okay here since the number of disks on the tower is
    // guaranteed to be [0, UINT_MAX]
    return (unsigned)(disks_.size());
}


unsigned Tower::size_of_top() const
{
    assert(!is_diskless());
    return disks_.back().size();
}


unsigned Tower::size_of_largest_disk() const
{
    assert(!is_diskless());
    unsigned largest = size_of_disk_at(0);
    for(unsigned i = 0; i < num_disks(); i++) {
        if(size_of_disk_at(i) > largest) largest = size_of_disk_at(i);
    }
    return largest;
}


unsigned Tower::size_of_disk_at(unsigned index) const
{
    assert(!is_diskless());
    return disks_.at(index).size();
}


bool Tower::is_diskless() const { return num_disks() == 0; }


bool Tower::are_strictly_decreasing() const
{
    assert(!is_diskless());
    unsigned expected = size_of_disk_at(0);
    for(unsigned i = 0; i < num_disks(); i++) {
        if(size_of_disk_at(i) != expected) return false;
        expected--;
    }
    return true;
}


const Disk& Tower::disk_at(unsigned index) const
{
    assert(!is_diskless());
    return disks_.at(index);
}


void Tower::top_to_top(Tower& dest_tower)
{
    assert(dest_tower.num_disks() < UINT_MAX);
    assert(!is_diskless());
    Disk diskToMove = disks_.back();
    disks_.pop_back();
    dest_tower.disks_.push_back(diskToMove);
}


bool Tower::compare(const Tower& T) const
{
    if(T.num_disks() != num_disks()) return false;
    if(T.is_diskless() && is_diskless()) return true;
    for(unsigned i = 0; i < num_disks(); i++) {
        if(T.disk_at(i).size() != disk_at(i).size()) return false;
    }
    return true;
}


unsigned highestTower(const std::vector<Tower>& towers)
{
    assert(!towers.empty());
    unsigned highest = 0;
    for(size_t i = 0; i < towers.size(); i++) {
        if(towers.at(i).num_disks() > highest) {
            highest = towers.at(i).num_disks();
        }
    }
    return highest;
}
