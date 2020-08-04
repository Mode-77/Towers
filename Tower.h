#pragma once

#include "Disk.h"
#include <vector>

#include "unit_tests.h"

class Tower {
public:
    Tower();
    Tower(int num_disks);

    size_t num_disks() const;
    int size_of_top() const;
    int size_of_largest_disk() const;
    int size_of_disk_at(size_t place) const;
    bool is_diskless() const;
    bool are_strictly_decreasing() const;
    const Disk& disk_at(size_t index) const;
    void top_to_top(Tower& dest_tower);
    bool compare(const Tower&) const;

private:
    std::vector<Disk> disks_;
};










template<typename T> struct List {

    void add(const T&);
    void remove(size_t index);
    void clear();

    T& front();
    T& back();
    T& at(size_t index);
    const T& at(size_t index) const;

    size_t length() const;
    bool isEmpty() const;

protected:
    std::vector<T> internalStruct;
};


template<typename T>
void List<T>::add(const T& t)
{
    internalStruct.push_back(t);
}


template<typename T>
void List<T>::remove(size_t index)
{
    internalStruct.erase(internalStruct.begin() + index);
}


template<typename T>
void List<T>::clear()
{
    internalStruct.clear();
}


template<typename T>
T& List<T>::at(size_t index)
{
    return internalStruct.at(index);
}


template<typename T>
const T& List<T>::at(size_t index) const
{
    return internalStruct.at(index);
}


template<typename T>
T& List<T>::front()
{
    return internalStruct.front();
}


template<typename T>
T& List<T>::back()
{
    return internalStruct.back();
}


template<typename T>
size_t List<T>::length() const
{
    return internalStruct.size();
}


template<typename T>
bool List<T>::isEmpty() const
{
    return internalStruct.empty();
}



struct TowerList: List<Tower> {
    size_t highest_tower() const;
    bool compare(const TowerList&) const;
};


struct PerfectHanoi {
    PerfectHanoi(size_t num_disks);
    void do_next_move();
    bool compare(const TowerList&) const;

private:
    //bool equals(const int* X, const int* Y) const;
    //void swap(int* X) const;
    //bool is_best_move(int* actual, const int* best) const;
    void do_valid_action(Tower& X, Tower& Y) const;


    TowerList towers;
    const size_t starting_num_disks;
    const int odd_num_disks;
    int thinker;


    const int best_moves[2][3][2] =
    {
        {
            { 0, 1 },
        { 0, 2 },
        { 1, 2 }
        },

    {
        { 0, 2 },
        { 0, 1 },
        { 1, 2 }
    }
    };
};



class TowerDrawer {
public:
    TowerDrawer(int pole_height);
    int pole_height() const;
    size_t draw(const Tower&) const;
    size_t draw(const TowerList&) const;

private:
    void draw_spaces(const int num_spaces = 1) const;
    int num_slashes(const int disk_size) const;
    int num_chars(const int disk_size) const;
    int center_of(const int disk_size) const;
    void draw_disk_row(const int disk_index, const Tower&) const;
    void draw_rod_row(const Tower&) const;
    void draw_rod_top(const Tower&) const;
    void draw_tower_row(int row, const Tower&) const;


    int pole_height_;
};