//
// Created by denys on 3/24/2024.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include <SFML/Graphics.hpp>
#include <random>

#include "Global.h"

class Cell {
private:
    unsigned int x;
    unsigned int y;
    bool is_bomb;
    bool is_open;
    bool is_flagged;

    unsigned int bombs_around;
    unsigned int mouse_state;

public:
    Cell();
    Cell(unsigned int x, unsigned int y);
    void reset();

    bool get_is_bomb();
    bool get_is_open();
    bool get_is_flagged();

    unsigned int get_bombs_around();
    unsigned int get_mouse_state();

    void count_bombs_around(std::vector<std::vector<Cell>>& cells);
    bool open(std::vector<std::vector<Cell>>& cells);
    void flag();
    void set_bomb();
    void set_mouse_state(unsigned int mouse_state);



};


#endif //MINESWEEPER_CELL_H
