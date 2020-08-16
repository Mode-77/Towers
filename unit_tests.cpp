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
    cout << endl;
}

void Test_tower_drawing(const int first_tower_size, const int last_tower_size)
{
    for(int i = first_tower_size; i <= last_tower_size; i++) {
        cout << "[" << i << "]:" << endl;
        TowerDrawer td(1 + i);
        td.draw(Tower(i));
        cout << endl;
    }
    /*
    for(int i = first_tower_size; i <= last_tower_size; i++) {
        cout << "[" << i << "]:" << endl;
        int h = (i != 0) ? i : 1;
        Tower tower(i, h, 1);
        std::vector<Tower> towers;
        towers.push_back(tower);
        draw_towers(towers);
        cout << endl;
    }
    */
}

void Test_tower_list_drawing()
{
    TowerDrawer td(4);
    TowerList t;
    t.add(Tower(3));
    t.add(Tower(2));
    t.add(Tower(1));
    td.draw(t);
    cout << endl;
}

void Putting_on_diskless_tower_makes_size_one()
{
    /*
    std::vector<Tower> towers;

    towers.push_back(Tower(0, 3, 1));
    assert(towers.at(0).num_disks() == 0);
    draw_towers(towers);
    cout << endl;

    towers.at(0).putDisk(Disk(5), 0);
    assert(towers.at(0).num_disks() == 1);
    draw_towers(towers);
    cout << endl;

    towers.at(0).putDisk(Disk(6), 1);
    assert(towers.at(0).num_disks() == 2);
    draw_towers(towers);
    cout << endl;
    */
}

void Test_top_to_top()
{
    TowerList test_tower_list;

    test_tower_list.add(Tower());
    test_tower_list.add(Tower());

    TowerDrawer td(5);
    td.draw(test_tower_list);
    cout << endl;

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
    cout << endl;

    tower_a.top_to_top(tower_b);
    tower_a.top_to_top(tower_c);


    assert(tower_a.num_disks() == 1);
    assert(tower_b.num_disks() == 1);
    assert(tower_c.num_disks() == 1);

    td.draw(test_tower_list);
    cout << endl;
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
