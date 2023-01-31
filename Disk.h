#ifndef DISK_H
#define DISK_H

struct Disk {
    /*
        Constructs a disk with a size

        size > 0
    */
    Disk(unsigned size);

    /*
        Draws the disk to standard output
    */
    void draw() const;

    /*
        Returns the size of the disk
    */
    unsigned size() const;

private:
    unsigned size_;
};

void draw_solid_style(Disk);
void draw_slash_bracket_style(Disk);

#endif
