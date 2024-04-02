//
// Created by denys on 3/24/2024.
//

#include <iostream>
#include "headers/Map.h"

Map::Map() : cells(gbl::ROWS, std::vector<Cell>(gbl::COLUMNS)), game_over(false), random_engine(random_device()){
    for(unsigned int i = 0; i < gbl::ROWS; i++){
        for(unsigned int j = 0; j < gbl::COLUMNS; j++){
            cells[i][j] = Cell(i, j);
        }
    }

    std::uniform_int_distribution<unsigned int> x_distribution(0, gbl::ROWS - 1);
    std::uniform_int_distribution<unsigned int> y_distribution(0, gbl::COLUMNS - 1);

    for(unsigned int i = 0; i < gbl::BOMBS; i++){
        unsigned int bomb_x = static_cast<unsigned int>(x_distribution(random_engine));
        unsigned int bomb_y = static_cast<unsigned int>(y_distribution(random_engine));

        if(cells[bomb_x][bomb_y].get_is_bomb()){
            i--;
        }
        else{
            cells[bomb_x][bomb_y].set_bomb();
        }
    }
    for(unsigned int i = 0; i < gbl::ROWS; i++){
        for(unsigned int j = 0; j < gbl::COLUMNS; j++){
            cells[i][j].count_bombs_around(cells);
        }
    }
}
void Map::draw(sf::RenderWindow& window){
    sf::RectangleShape cell_shape(sf::Vector2f(gbl::CELL_SIZE - 1, gbl::CELL_SIZE - 1));

    sf::Sprite icon_sprite;
    sf::Texture icon_texture;

    icon_texture.loadFromFile("../Resources/Icons" + std::to_string(gbl::CELL_SIZE) + ".png");
    icon_sprite.setTexture(icon_texture);

    for(unsigned int i = 0; i < gbl::ROWS; i++){
        for(unsigned int j = 0; j < gbl::COLUMNS; j++){
            cell_shape.setPosition(static_cast<float>(gbl::CELL_SIZE * i), static_cast<float>(gbl::CELL_SIZE * j));

            if(cells[i][j].get_is_open()){
                unsigned int bombs_around = cells[i][j].get_bombs_around();

                cell_shape.setFillColor(sf::Color(65, 68, 74));

                window.draw(cell_shape);

                if(bombs_around > 0){
                    icon_sprite.setPosition(static_cast<float>(gbl::CELL_SIZE * i), static_cast<float>(gbl::CELL_SIZE * j));
                    icon_sprite.setTextureRect(sf::IntRect(gbl::CELL_SIZE * bombs_around, 0, gbl::CELL_SIZE, gbl::CELL_SIZE));

                    window.draw(icon_sprite);
                }
            }
            else{
                cell_shape.setFillColor(sf::Color(128, 128, 128));

                if(!game_over){
                    if(cells[i][j].get_mouse_state() == 1){
                        cell_shape.setFillColor(sf::Color(128, 128, 128));
                    }
                    else if(cells[i][j].get_mouse_state() == 2){
                        cell_shape.setFillColor(sf::Color(128, 128, 128));
                    }
                }
                window.draw(cell_shape);
                if(cells[i][j].get_is_flagged()){
                    icon_sprite.setPosition(static_cast<float>(gbl::CELL_SIZE * i), static_cast<float>(gbl::CELL_SIZE* j));
                    icon_sprite.setTextureRect(sf::IntRect(0, 0, gbl::CELL_SIZE, gbl::CELL_SIZE));

                    window.draw(icon_sprite);
                }
            }
            cells[i][j].set_mouse_state(0);
        }
    }
}

void Map::restart() {
    if(game_over){
        game_over = false;
        for(unsigned int i = 0; i < gbl::ROWS; i++){
            for(unsigned int j = 0; j < gbl::COLUMNS; j++){
                cells[i][j].reset();
            }
        }
    }
}

void Map::open_cell(unsigned int x, unsigned int y) {
    if(!game_over && !cells[x][y].get_is_flagged()){
        if(cells[x][y].open(cells)){
            game_over = true;
        }
        else{
            unsigned int total_closed_cells = 0;

            for(auto v : cells){
                for(Cell c : v) {
                    total_closed_cells += 1 - c.get_is_open();
                }
            }
            if(gbl::BOMBS == total_closed_cells){
                game_over = true;
            }
        }
    }
}

bool Map::get_game_over() {
    return game_over;
}

unsigned int Map::get_flags() {
    unsigned int nr_flags = 0;
    for(auto v : cells){
        for(Cell c : v){
            if(c.get_is_flagged()){
                nr_flags++;
            }
        }
    }
    return nr_flags;
}

void Map::flag_cell(unsigned int x, unsigned int y) {
    if(!game_over){
        cells[x][y].flag();
    }
}

void Map::set_mouse_state(unsigned int state, unsigned int x, unsigned int y) {
    cells[x][y].set_mouse_state(state);
    return;
}
