#include "Disk.h"
#include <cassert>
#include <iostream>

Disk::Disk(unsigned size): size_(size)
{
    assert(size_ > 0);
}

unsigned Disk::size() const { return size_; }

void drawDisk(const Disk d, char filling)
{
    std::cout << '[';   // Left edge of the disk
    unsigned j = 2 * d.size() + 1;
    if(d.size() >= 10 && d.size() <= 99) j--;
    for(unsigned i = 0; i < j; i++) {
        const unsigned DISK_CENTER = (2 * d.size() + 1) / 2;
        if(i == DISK_CENTER) std::cout << d.size();
        else if(i == (DISK_CENTER - 1)) std::cout << ' ';
        else if(i == (DISK_CENTER + 1)) std::cout << ' ';
        else std::cout << filling;
    }
    std::cout << ']';   // Right edge of the disk
}
