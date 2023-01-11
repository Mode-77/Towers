#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "defines.h"

#include "Tower.h"
#include "TowerDrawer.h"
#include "PerfectHanoi.h"

using namespace std;

#ifdef RUN_UNIT_TESTS
#include "unit_tests.h"
#endif


#ifndef RUN_UNIT_TESTS

unsigned least_possible(size_t num_disks)
{
    return pow(2, num_disks) - 1;
}


double get_score(size_t num_disks, unsigned moves)
{
    return round(100.0 * least_possible(num_disks) / moves);
}


void show_results(size_t num_disks, unsigned moves)
{
    cout << "You finished in "\
        << moves << " moves" << endl;

    cout << "Best possible is "\
        << least_possible(num_disks) << " moves" << endl;

    cout << "Your score: " << get_score(num_disks, moves) << "%" << endl;
}


double progress_remaining(int moves_remaining, int total_possible)
{
    return (double)moves_remaining / total_possible;
}


double progress_made(int moves_remaining, int total_possible)
{
    return 1 - progress_remaining(moves_remaining, total_possible);
}


double hit_milestone(double inc, double amount)
{
    return amount / inc;
}


void show_progress_message(int which_milestone)
{
    switch(which_milestone) {
    case 1: cout << "You're doing great! Keep going!" << endl; break;
    case 2: cout << "You're halfway there! Keep it up!" << endl; break;
    case 3: cout << "You've almost got it! Don't stop!" << endl; break;
    case 4: cout << "You did it!" << endl; break;
    }
}


void redraw_towers(const TowerList& T, const TowerDrawer& TD)
{
    system("clear");
    TD.draw(T);
}

#endif


int main(int argc, char** argv)
{
#ifdef RUN_UNIT_TESTS

    New_tower_is_diskless();
    Number_of_disks_match_expected();
    Disks_are_strictly_decreasing();
    Drawing_empty_tower_list_does_nothing();
    Drawing_diskless_tower_draws_entire_rod();
    Test_disk_drawing(1, 10);
    Test_tower_drawing(0, 10);
    Test_tower_list_drawing();
    Test_top_to_top();
    Test_region_drawing();

#else

    const int NUM_DISKS = 1;

    PerfectHanoi perfect_game(NUM_DISKS);

    TowerList towers;
    towers.add(Tower(NUM_DISKS));
    towers.add(Tower());
    towers.add(Tower());

    const Tower& goal_tower = towers.back();

    int moves = 0;
    int moves_left = least_possible(NUM_DISKS);
    bool asked_for_first_move = false;
    bool was_best_move = true;
    int current_progress_point = 0;

    TowerDrawer tower_drawer(NUM_DISKS + 3);

    redraw_towers(towers, tower_drawer);

    cout << "Good luck!" << endl << endl;

    while(goal_tower.num_disks() != NUM_DISKS) {
        if(!asked_for_first_move) {
            cout << "What's your first move? ";
            asked_for_first_move = true;
        }
        else cout << "What's your next move? ";

        string input("");
        getline(cin, input);

        if(input == "quit") {
            break;
        }

        int from = stoi(input.substr(0, 1)) - 1;
        int to = stoi(input.substr(2, 1)) - 1;

        // Do tower list bounds checking here

        Tower& tower_from = towers.at(from);
        Tower& tower_to = towers.at(to);



        if(tower_from.is_diskless()) {
            redraw_towers(towers, tower_drawer);
            cout << "Nothing on " << from + 1 << "..." << endl << endl;
        }
        else if(!tower_to.is_diskless() &&
            (tower_from.size_of_top() > tower_to.size_of_top())) {

            redraw_towers(towers, tower_drawer);
            cout << "Can't place larger disk on smaller disk..." << endl << endl;
        }
        else {
            if(was_best_move) perfect_game.do_next_move();
            tower_from.top_to_top(tower_to);

            redraw_towers(towers, tower_drawer);

            if(perfect_game.compare(towers)) {
                was_best_move = true;
                moves_left--;

                int new_progress_point =
                    hit_milestone(0.25, progress_made(moves_left, least_possible(NUM_DISKS)));

                if(new_progress_point > current_progress_point) {
                    current_progress_point = new_progress_point;
                    show_progress_message(current_progress_point);
                }
            }
            else was_best_move = false;
            moves++;

            if((moves == 3) && (moves_left == least_possible(NUM_DISKS) - 3)) {
                cout << "Good first moves! Keep it up!" << endl << endl;
            }
        }
    }

    if(goal_tower.num_disks() == NUM_DISKS) {
        show_results(NUM_DISKS, moves);
    }

#endif

    return 0;
}
