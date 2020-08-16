#include "PerfectHanoi.h"




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

void PerfectHanoi::do_valid_action(Tower& X, Tower& Y) const
{
    if(X.is_diskless()) Y.top_to_top(X);
    else if(Y.is_diskless()) X.top_to_top(Y);
    else if(X.size_of_top() < Y.size_of_top()) X.top_to_top(Y);
    else Y.top_to_top(X);
}
