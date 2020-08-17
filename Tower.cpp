#include "Tower.h"
#include "Disk.h"
#include <cassert>
#include <iostream>

using namespace std;



Tower::Tower()
{

}


Tower::Tower(size_t num_disks)
{
    assert(num_disks >= 0);
    for(int i = num_disks; i > 0; i--) {
        disks_.push_back(Disk(i));
    }
}


size_t Tower::num_disks() const { return disks_.size(); }


int Tower::size_of_top() const
{
    assert(!is_diskless());
    return disks_.back().size();
}


int Tower::size_of_largest_disk() const
{
    assert(!is_diskless());
    int largest = 0;
    for(size_t u = 0; u < num_disks(); u++) {
        if(size_of_disk_at(u) > largest) largest = size_of_disk_at(u);
    }
    return largest;
}


int Tower::size_of_disk_at(size_t place) const
{
    assert(!is_diskless());
    return disks_.at(place).size();
}


bool Tower::is_diskless() const { return num_disks() == 0; }


bool Tower::are_strictly_decreasing() const
{
    assert(!is_diskless());
    size_t expected = num_disks();
    for(size_t j = 0; j < num_disks(); j++) {
        if(size_of_disk_at(j) != expected) return false;
        expected--;
    }
    return true;
}


const Disk& Tower::disk_at(size_t i) const
{
    assert(!is_diskless());
    return disks_.at(i);
}


void Tower::top_to_top(Tower& dest_tower)
{
    assert(!is_diskless());
    Disk diskToMove = disks_.back();
    disks_.pop_back();
    dest_tower.disks_.push_back(diskToMove);
}


bool Tower::compare(const Tower& T) const
{
    if(T.num_disks() != num_disks()) return false;
    if(T.is_diskless() && is_diskless()) return true;
    for(size_t disk = 0; disk < num_disks(); disk++) {
        if(T.disk_at(disk).size() != disk_at(disk).size()) return false;
    }
    return true;
}



size_t TowerList::highest_tower() const
{
    assert(!isEmpty());
    size_t highest = 0;
    for(size_t i = 0; i < length(); i++) {
        if(at(i).num_disks() > highest) {
            highest = at(i).num_disks();
        }
    }
    return highest;
}


bool TowerList::compare(const TowerList& T) const
{
    if(T.length() != length()) return false;
    for(size_t tower = 0; tower < length(); tower++) {
        if(!(T.at(tower).compare(at(tower)))) return false;
    }
    return true;
}
