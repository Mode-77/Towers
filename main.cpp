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


void PrintResults(size_t num_disks, unsigned moves)
{
    cout << "You finished in " << moves << " moves\n";

    cout << "Best possible is "\
        << least_possible(num_disks) << " moves\n";

    cout << "Your score: " << get_score(num_disks, moves) << "%\n";
}


void DrawTowers(const TowerList& towerList, const TowerDrawer& towerDrawer)
{
    system("clear");
    towerDrawer.draw(towerList);
}


void PrintStatus(const string& statusMessage)
{
    cout << "\n";
    cout << statusMessage << "\n";
    cout << "\n";
}


void AskQuestion(const string& question)
{
    cout << question;
}


string GetRawInput()
{
    string input;
    getline(cin, input);
    return input;
}


// 0 = Input is correct move syntax
// 1 = Input is empty
// 2 = Input is "quit"
int ProcessInput(const string& input)
{
    if(input.empty()) return 1;
    if(!input.compare("quit")) return 2;
    return 0;
}


// 0 = Input is a valid move
// 1 = Taking from a diskless tower
// 2 = Putting a larger disk on a smaller disk
int CheckForValidMove(const string& input, const TowerList& towerList)
{
    int from = stoi(input.substr(0, 1)) - 1;
    int to = stoi(input.substr(2, 1)) - 1;
    const Tower& towerFrom = towerList.at(from);
    const Tower& towerTo = towerList.at(to);
    if(towerFrom.is_diskless()) return 1;
    if(!towerTo.is_diskless() &&
        (towerFrom.size_of_top() > towerTo.size_of_top())) return 2;
    return 0;
}


void DoMove(const string& move, TowerList& towerList)
{
    int from = stoi(move.substr(0, 1)) - 1;
    int to = stoi(move.substr(2, 1)) - 1;
    Tower& towerFrom = towerList.at(from);
    Tower& towerTo = towerList.at(to);
    towerFrom.top_to_top(towerTo);
}


bool CheckForGameWon(const Tower& goalTower, int totalDisks)
{
    return goalTower.num_disks() == totalDisks;
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

    TowerList towers;
    towers.add(Tower(NUM_DISKS));
    towers.add(Tower());
    towers.add(Tower());

    const Tower& goalTower = towers.back();
    TowerDrawer tower_drawer(NUM_DISKS + 3);

    int moves = 0;
    bool requestQuit = false;
    bool won = false;
    string status, question, rawInput;
    status = "Good luck!";
    question = "What's your first move? ";
    while(!(requestQuit || won)) {
        DrawTowers(towers, tower_drawer);
        PrintStatus(status);
        AskQuestion(question);
        rawInput = GetRawInput();

        switch(ProcessInput(rawInput)) {
        case 0: break;
        case 1: continue;
        case 2:
            {
                requestQuit = true;
                continue;
            }
        }

        switch(CheckForValidMove(rawInput, towers)) {
        case 0:
            {
                DoMove(rawInput, towers);
                moves++;
                won = CheckForGameWon(goalTower, NUM_DISKS);
                status = "";
                question = "What's your next move? ";
                continue;
            }
        case 1:
            {
                status = "Nothing on that tower...";
                continue;
            }
        case 2:
            {
                status = "Can't place a larger disk on a smaller disk...";
                continue;
            }
        }
    }

    if(won) {
        DrawTowers(towers, tower_drawer);
        PrintStatus("You win!");
        PrintResults(NUM_DISKS, moves);
    }

#endif

    return 0;
}
