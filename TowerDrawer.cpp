#include "TowerDrawer.h"
#include "Tower.h"
#include <cassert>
#include <iostream>
#include <climits>

TowerDrawer::TowerDrawer(unsigned pole_height): pole_height_(pole_height)
{}


unsigned TowerDrawer::pole_height() const { return pole_height_; }


size_t TowerDrawer::draw(const Tower& T) const
{
    std::vector<Tower> tempTowerVector;
    tempTowerVector.push_back(T);
    return draw(tempTowerVector);
}


size_t TowerDrawer::draw(const std::vector<Tower>& towers) const
{
    if(towers.empty()) return 0;
    assert(pole_height_ > highestTower(towers));
    for(unsigned i = 0; i <= pole_height_; i++) {
        for(size_t t = 0; t < towers.size(); t++) {
            draw_tower_row(pole_height_ - i, towers.at(t));
            draw_spaces(12);
        }
        std::cout << "\n";
    }
    return towers.size();
}


void TowerDrawer::set_pole_height(unsigned pole_height)
{
    pole_height_ = pole_height;
}


void TowerDrawer::draw_spaces(unsigned n) const
{
    for(; n > 0; n--) std::cout << " ";
}


unsigned TowerDrawer::num_slashes(const unsigned disk_size) const
{
    return disk_size * 2 + 1;
}


unsigned TowerDrawer::num_chars(const unsigned disk_size) const
{
    return 2 + num_slashes(disk_size);
}


unsigned TowerDrawer::center_of(const unsigned disk_size) const
{
    return (num_chars(disk_size) - 1) / 2;
}


void TowerDrawer::draw_disk_row(const unsigned disk_index, const Tower& t) const
{
    draw_spaces(center_of(t.size_of_largest_disk()) - center_of(t.size_of_disk_at(disk_index)));
    if(!(t.size_of_disk_at(disk_index) & 1)) drawDisk(t.disk_at(disk_index), '/');
    else drawDisk(t.disk_at(disk_index), ' ');
    draw_spaces(center_of(t.size_of_largest_disk()) - center_of(t.size_of_disk_at(disk_index)));
}


void TowerDrawer::draw_rod_row(const Tower& t) const
{
    if(t.is_diskless()) {
        draw_spaces();
        std::cout << "|_|";
        draw_spaces();
        return;
    }
    draw_spaces(center_of(t.size_of_largest_disk()) - 1);
    std::cout << "|_|";
    draw_spaces(center_of(t.size_of_largest_disk()) - 1);
}


void TowerDrawer::draw_rod_top(const Tower& t) const
{
    if(t.is_diskless()) {
        draw_spaces(2);
        std::cout << "_";
        draw_spaces(2);
        return;
    }
    draw_spaces(center_of(t.size_of_largest_disk()));
    std::cout << "_";
    draw_spaces(center_of(t.size_of_largest_disk()));
}


// todo: draws funnily when tower.num_disks() == tower.height()
void TowerDrawer::draw_tower_row(unsigned row, const Tower& tower) const
{
    assert(row <= pole_height_);
    if(row == pole_height_) draw_rod_top(tower);
    else if(row >= tower.num_disks()) draw_rod_row(tower);
    else draw_disk_row(row, tower);
}
