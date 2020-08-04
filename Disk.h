#pragma once

struct Disk {
    // size > 0
    Disk(const int size);

    void draw() const;
    int size() const;

private:
    int size_;
};

void draw_solid_style(const Disk);
void draw_slash_bracket_style(const Disk);
