#include "Disk.h"
#include <cassert>
#include <iostream>

Disk::Disk(unsigned size): size_(size)
{
    assert(size_ > 0);
}

void Disk::draw() const
{
    for(unsigned i = 0; i < (2 * size() + 1); i++) {
        std::cout << '+';
    }
}

unsigned Disk::size() const { return size_; }

void draw_solid_style(const Disk d)
{
    std::cout << '[';   // Left edge of the disk
    unsigned j = 2 * d.size() + 1;
    if(d.size() >= 10 && d.size() <= 99) j--;
    for(unsigned i = 0; i < j; i++) {
        const unsigned DISK_CENTER = (2 * d.size() + 1) / 2;
        if(i == DISK_CENTER) std::cout << d.size();
        else std::cout << ' ';
    }
    std::cout << ']';   // Right edge of the disk
}

void draw_slash_bracket_style(const Disk d)
{
    std::cout << '[';   // Left edge of the disk
    unsigned j = 2 * d.size() + 1;
    if(d.size() >= 10 && d.size() <= 99) j--;
    for(unsigned i = 0; i < j; i++) {
        const unsigned DISK_CENTER = (2 * d.size() + 1) / 2;
        if(i == DISK_CENTER) std::cout << d.size();
        else if(i == (DISK_CENTER - 1)) std::cout << ' ';
        else if(i == (DISK_CENTER + 1)) std::cout << ' ';
        else std::cout << '/';
    }
    std::cout << ']';   // Right edge of the disk
}
