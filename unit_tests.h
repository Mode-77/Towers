#pragma once

class Tower;

void Number_of_disks_match_expected();

void Disks_are_strictly_decreasing();

void Row_zero_is_always_top_disk();

void Moving_disk_diminishes_one_size_and_increases_another();

void Test_tower_list_drawing();

void Putting_on_diskless_tower_makes_size_one();

void Test_top_to_top();

void Drawing_empty_tower_list_does_nothing();

void Drawing_diskless_tower_draws_entire_rod();

void Test_disk_drawing(const int firstDiskSize, const int lastDiskSize, int style = 0);

void Test_tower_drawing(const int first_tower_size, const int last_tower_size);
