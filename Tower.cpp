#include "Tower.h"
#include "Disk.h"
#include <cassert>
#include <iostream>

using namespace std;



Tower::Tower()
{

}


Tower::Tower(int num_disks)
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

bool Tower::compare(const Tower& T) const
{
    if(T.num_disks() != num_disks()) return false;
    if(T.is_diskless() && is_diskless()) return true;
    for(size_t disk = 0; disk < num_disks(); disk++) {
        if(T.disk_at(disk).size() != disk_at(disk).size()) return false;
    }
    return true;
}

bool TowerList::compare(const TowerList& T) const
{
    if(T.length() != length()) return false;
    for(size_t tower = 0; tower < length(); tower++) {
        if(!(T.at(tower).compare(at(tower)))) return false;
    }
    return true;
}



PerfectHanoi::PerfectHanoi(size_t num_disks):
    starting_num_disks(num_disks),
    odd_num_disks(starting_num_disks & 1),
    thinker(0)
{
    towers.add(Tower(num_disks));
    towers.add(Tower());
    towers.add(Tower());
}

void PerfectHanoi::do_next_move()
{
    if(towers.back().num_disks() == starting_num_disks) return;
    Tower& a = towers.at(best_moves[odd_num_disks][thinker][0]);
    Tower& b = towers.at(best_moves[odd_num_disks][thinker][1]);
    do_valid_action(a, b);
    if((++thinker) == 3) thinker = 0;
}

bool PerfectHanoi::compare(const TowerList& T) const
{
    return towers.compare(T);
}
/*
bool PerfectHanoi::equals(const int* X, const int* Y) const
{
    return (X[0] == Y[0]) && (X[1] == Y[1]);
}

void PerfectHanoi::swap(int* X) const
{
    int temp = X[1];
    X[1] = X[0];
    X[0] = temp;
}

bool is_best_move(int* actual, const int* best)
{
    if(equals(actual, best)) return true;
    swap(actual);
    return equals(actual, best);
}

void do_best_possible(TowerList& towers)
{
    static int cpu_choice =
    // do the valid action between A and C
    do_valid_action(towers[0], towers[2]);
    // do the valid action between A and B
    do_valid_action(towers[0], towers[1]);
    // do the valid action between B and C
    do_valid_action(towers[1], towers[2]);
}
*/

void PerfectHanoi::do_valid_action(Tower& X, Tower& Y) const
{
    if(X.is_diskless()) Y.top_to_top(X);
    else if(Y.is_diskless()) X.top_to_top(Y);
    else if(X.size_of_top() < Y.size_of_top()) X.top_to_top(Y);
    else Y.top_to_top(X);
}