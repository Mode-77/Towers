#ifndef TOWER_DRAWER
#define TOWER_DRAWER

#include <cstddef>
#include <vector>

class Tower;

class TowerDrawer {
public:
    TowerDrawer(unsigned pole_height);
    unsigned pole_height() const;
    size_t draw(const Tower&) const;
    size_t draw(const std::vector<Tower>&) const;
    void set_pole_height(unsigned pole_height);

private:
    void draw_spaces(unsigned num_spaces = 1) const;
    unsigned num_slashes(unsigned disk_size) const;
    unsigned num_chars(unsigned disk_size) const;
    unsigned center_of(unsigned disk_size) const;
    void draw_disk_row(unsigned disk_index, const Tower&) const;
    void draw_rod_row(const Tower&) const;
    void draw_rod_top(const Tower&) const;
    void draw_tower_row(unsigned row, const Tower&) const;

    unsigned pole_height_;
};

#endif
