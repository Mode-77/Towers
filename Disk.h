#ifndef DISK_H
#define DISK_H

struct Disk {
    /*
        Constructs a disk with a size

        size > 0
    */
    Disk(unsigned size);

    /*
        Returns the size of the disk
    */
    unsigned size() const;

private:
    unsigned size_;
};

void drawDisk(Disk d, char filling);

#endif
