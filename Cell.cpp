//
// Created by denys on 3/24/2024.
//

#include <iostream>
#include "headers/Cell.h"

Cell::Cell(unsigned int x, unsigned int y) : x(x), y(y), is_bomb(false), is_open(false), is_flagged(false){

}
Cell::Cell() : x(0), y(0), is_bomb(false), is_open(false), is_flagged(false){

}

void Cell::reset(){
    is_bomb = false;
    is_open = false;
    is_flagged = false;
}

bool Cell::get_is_bomb() {
    return is_bomb;
}

bool Cell::get_is_open() {
    return is_open;
}

bool Cell::get_is_flagged() {
    return is_flagged;
}

unsigned int Cell::get_bombs_around() {
    return bombs_around;
}

unsigned int Cell::get_mouse_state() {
    return mouse_state;
}

void Cell::count_bombs_around(std::vector<std::vector<Cell>>& cells) {
    bombs_around = 0;

    if(is_bomb == 0){
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if((i == 0 && j == 0) || (i + x < 0 || j + y < 0 || i + x >= gbl::COLUMNS || j + y >= gbl::ROWS)){
                    continue;
                }
                if(cells[i + x][j + y].is_bomb){
                    bombs_around++;
                    //std::cout<<bombs_around<<" "<< i + x << " " << j + y<< "     ";
                }
            }
        }
    }
}

bool Cell::open(std::vector<std::vector<Cell>> &cells) {
    if(is_open == 0) {
        is_open = 1;
        if (is_bomb == 0 && bombs_around == 0) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if ((i == 0 && j == 0) || (i + x < 0 || j + y < 0 || i + x >= gbl::COLUMNS || j + y >= gbl::ROWS)) {
                        continue;
                    }
                    cells[i + x][j + y].open(cells);
                }
            }
        }
        return is_bomb;
    }
    return false;
}

void Cell::flag() {
    if(is_open == 0){
        is_flagged = 1 - is_flagged;
    }
}

void Cell::set_bomb() {
    is_bomb = true;
}

void Cell::set_mouse_state(unsigned int state) {
    mouse_state = state;
}





