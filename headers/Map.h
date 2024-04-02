//
// Created by denys on 3/24/2024.
//

#ifndef MINESWEEPER_MAP_H
#define MINESWEEPER_MAP_H
#include <SFML/Graphics.hpp>
#include <random>

#include "Cell.h"
#include "Global.h"

class Map {
private:
    std::vector<std::vector<Cell>> cells;
    bool game_over;

    std::default_random_engine random_engine;
    std::random_device random_device;

public:
    Map();
    void draw(sf::RenderWindow& window);
    void restart();
    void open_cell(unsigned int x, unsigned int y);
    void flag_cell(unsigned int x, unsigned int y);

    bool get_game_over();
    unsigned int get_flags();
    void set_mouse_state(unsigned int state, unsigned int x, unsigned int y);
};


#endif //MINESWEEPER_MAP_H
