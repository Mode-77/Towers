#include "TowerDrawer.h"
#include "Disk.h"
#include <cassert>
#include <iostream>

using namespace std;



TowerDrawer::TowerDrawer(int pole_height): pole_height_(pole_height)
{}


int TowerDrawer::pole_height() const { return pole_height_; }


size_t TowerDrawer::draw(const Tower& T) const
{
    TowerList temp_tower_list;
    temp_tower_list.add(T);
    return draw(temp_tower_list);
}


size_t TowerDrawer::draw(const TowerList& list) const
{
    if(list.isEmpty()) return 0;
    assert(pole_height_ > list.highest_tower());
    for(int i = pole_height_; i >= 0; i--) {
        for(size_t t = 0; t < list.length(); t++) {
            draw_tower_row(i, list.at(t));
            draw_spaces(12);
        }
        if(i != 0) cout << endl;
    }
    return list.length();
}


int to_signed(const unsigned x)
{
    if(x <= INT_MAX)
        return static_cast<int>(x);

    if(x >= INT_MIN)
        return static_cast<int>(x - INT_MIN) + INT_MIN;

    throw x; // Or whatever else you like
}


void TowerDrawer::draw_spaces(const int N) const
{
    assert(N >= 0);
    for(int i = 0; i < N; i++) cout << ' ';
}


int TowerDrawer::num_slashes(const int disk_size) const
{
    return disk_size * 2 + 1;
}


int TowerDrawer::num_chars(const int disk_size) const
{
    return 2 + num_slashes(disk_size);
}


int TowerDrawer::center_of(const int disk_size) const
{
    return (num_chars(disk_size) - 1) / 2;
}


void TowerDrawer::draw_disk_row(const int disk_index, const Tower& t) const
{
    draw_spaces(center_of(t.size_of_largest_disk()) - center_of(t.size_of_disk_at(disk_index)));
    if(!(t.size_of_disk_at(disk_index) & 1)) draw_slash_bracket_style(t.disk_at(disk_index));
    else draw_slash_bracket_style(t.disk_at(disk_index));
    draw_spaces(center_of(t.size_of_largest_disk()) - center_of(t.size_of_disk_at(disk_index)));
}


void TowerDrawer::draw_rod_row(const Tower& t) const
{
    if(t.is_diskless()) {
        draw_spaces();
        cout << "|_|";
        draw_spaces();
        return;
    }
    draw_spaces(center_of(t.size_of_largest_disk()) - 1);
    cout << "|_|";
    draw_spaces(center_of(t.size_of_largest_disk()) - 1);
}


void TowerDrawer::draw_rod_top(const Tower& t) const
{
    if(t.is_diskless()) {
        draw_spaces(2);
        cout << '_';
        draw_spaces(2);
        return;
    }
    draw_spaces(center_of(t.size_of_largest_disk()));
    cout << '_';
    draw_spaces(center_of(t.size_of_largest_disk()));
}


// todo: draws funnily when tower.num_disks() == tower.height()
void TowerDrawer::draw_tower_row(int row, const Tower& tower) const
{
    assert(row <= pole_height_);
    if(row == pole_height_) draw_rod_top(tower);
    else if(row >= tower.num_disks()) draw_rod_row(tower);
    else draw_disk_row(row, tower);
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
