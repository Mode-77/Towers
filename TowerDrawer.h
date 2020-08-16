#pragma once

class Tower;
class TowerList;


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
