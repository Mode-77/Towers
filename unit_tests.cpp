#include "defines.h"

#ifdef RUN_UNIT_TESTS

#include "unit_tests.h"
#include "Disk.h"
#include "Tower.h"
#include "TowerDrawer.h"

#include <cassert>
#include <iostream>

using namespace std;



void New_tower_is_diskless()
{
    Tower new_tower;
    assert(new_tower.is_diskless());
}

void Number_of_disks_match_expected()
{
    const int NUM_TRIALS = 1000;
    for(int num_disks = 0; num_disks <= NUM_TRIALS; num_disks++) {
        Tower test_tower(num_disks);
        assert(test_tower.num_disks() == num_disks);
    }
}

void Disks_are_strictly_decreasing()
{
    const int HIGHEST_TOWER_NUM_DISKS = 1000;
    for(int i = 1; i <= HIGHEST_TOWER_NUM_DISKS; i++) {
        Tower t(i);
        assert(t.are_strictly_decreasing());
    }
}

void Drawing_empty_tower_list_does_nothing()
{
    TowerDrawer td(0);
    TowerList empty_tower_list;
    assert(td.draw(empty_tower_list) == 0);
}

void Drawing_diskless_tower_draws_entire_rod()
{
    TowerDrawer td(1);
    TowerList test_tower_list;
    test_tower_list.add(Tower());
    td.draw(test_tower_list);
}

// firstDiskSize <= lastDiskSize
void Test_disk_drawing(const int firstDiskSize, const int lastDiskSize, int style)
{
    assert(firstDiskSize <= lastDiskSize);

    for(int i = firstDiskSize; i <= lastDiskSize; i++) {
        cout << "[" << i << "]:\t";
        Disk aTestDisk(i);

        switch(style) {
        case 0: aTestDisk.draw(); break;
        case 1: draw_slash_bracket_style(aTestDisk); break;
        default: aTestDisk.draw();
        }

        cout << endl;
    }
}

void Test_tower_drawing(const int first_tower_size, const int last_tower_size)
{
    for(int i = first_tower_size; i <= last_tower_size; i++) {
        cout << "[" << i << "]:" << endl;
        TowerDrawer td(1 + i);
        td.draw(Tower(i));
    }
}

void Test_tower_list_drawing()
{
    TowerDrawer td(4);
    TowerList t;
    t.add(Tower(3));
    t.add(Tower(2));
    t.add(Tower(1));
    td.draw(t);
}

void Test_top_to_top()
{
    TowerList test_tower_list;

    test_tower_list.add(Tower());
    test_tower_list.add(Tower());

    TowerDrawer td(5);
    td.draw(test_tower_list);

    //test_tower_list[0].top_to_top(test_tower_list[1]);    <- Uncomment to test assertion

    test_tower_list.clear();

    test_tower_list.add(Tower(3));
    test_tower_list.add(Tower());
    test_tower_list.add(Tower());

    Tower& tower_a = test_tower_list.at(0);
    Tower& tower_b = test_tower_list.at(1);
    Tower& tower_c = test_tower_list.at(2);

    assert(tower_a.num_disks() == 3);
    assert(tower_b.num_disks() == 0);
    assert(tower_c.num_disks() == 0);

    td.draw(test_tower_list);

    tower_a.top_to_top(tower_b);
    tower_a.top_to_top(tower_c);


    assert(tower_a.num_disks() == 1);
    assert(tower_b.num_disks() == 1);
    assert(tower_c.num_disks() == 1);

    td.draw(test_tower_list);
}

void Test_region_drawing()
{
    TowerList list;
    list.add(Tower());
    list.add(Tower());
    list.add(Tower());
    TowerDrawer drawer(9);
    drawer.draw(list);
    list.pop();
    list.add(Tower(3));
    drawer.draw(list);
}

#endif
