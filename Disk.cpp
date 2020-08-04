#include "Disk.h"
#include <cassert>
#include <iostream>


using namespace std;

Disk::Disk(const int size): size_(size)
{
    assert(size_ > 0);
}

void Disk::draw() const
{
    for(int i = 0; i < (2 * size() + 1); i++) {
        cout << '+';
    }
}

int Disk::size() const { return size_; }


void draw_solid_style(const Disk d)
{
    cout << '[';
    int j = 2 * d.size() + 1;
    if(d.size() >= 10 && d.size() <= 99) j--;
    for(int i = 0; i < j; i++) {
        if(i == (2 * d.size() + 1) / 2) cout << d.size();
        else cout << ' ';
    }
    cout << ']';
}


void draw_slash_bracket_style(const Disk d)
{
    cout << '[';
    int j = 2 * d.size() + 1;
    if(d.size() >= 10 && d.size() <= 99) j--;
    for(int i = 0; i < j; i++) {
        if(i == (2 * d.size() + 1) / 2) cout << d.size();
        else if(i == ((2 * d.size() + 1) / 2) - 1) cout << ' ';
        else if(i == ((2 * d.size() + 1) / 2) + 1) cout << ' ';
        else cout << '/';
    }
    cout << ']';
}
