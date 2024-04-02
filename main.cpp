#include <chrono>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/Global.h"
#include "headers/Map.h"

int main() {
    unsigned int lag = 0;

    std::chrono::time_point<std::chrono::steady_clock> previous_time;

    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(gbl::CELL_SIZE * gbl::COLUMNS * gbl::SCREEN_RESIZE, (gbl::FONT_HEIGHT + gbl::CELL_SIZE * gbl::COLUMNS) * gbl::SCREEN_RESIZE), "Minesweeper", sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, gbl::CELL_SIZE * gbl::COLUMNS, gbl::FONT_HEIGHT + gbl::CELL_SIZE * gbl::ROWS)));

    Map map;

    previous_time = std::chrono::steady_clock::now();

    while(window.isOpen() == 1){
        unsigned int delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

        lag += delta_time;

        previous_time += std::chrono::microseconds(delta_time);

        while(gbl::FRAME_DURATION <= lag){

            //unsigned char mouse_cell_x = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).x / static_cast<float>(gbl::CELL_SIZE * gbl::SCREEN_RESIZE))), 0, gbl::COLUMNS - 1);
            unsigned int mouse_cell_x = static_cast<int>(floor(sf::Mouse::getPosition(window).x)) / static_cast<float>(gbl::CELL_SIZE * gbl::SCREEN_RESIZE);
            if(mouse_cell_x < 0){
                mouse_cell_x = 0;
            }
            if(mouse_cell_x > gbl::COLUMNS - 1){
                mouse_cell_x = gbl::COLUMNS - 1;
            }

            unsigned int mouse_cell_y = static_cast<int>(floor(sf::Mouse::getPosition(window).y)) / static_cast<float>(gbl::CELL_SIZE * gbl::SCREEN_RESIZE);
            if(mouse_cell_y < 0){
                mouse_cell_y = 0;
            }
            if(mouse_cell_y > gbl::ROWS - 1){
                mouse_cell_y = gbl::ROWS - 1;
            }
            lag -= gbl::FRAME_DURATION;

            while(window.pollEvent(event) == 1){
                switch(event.type){
                    case sf::Event::Closed:{
                        window.close();
                        break;
                    }
                    case sf::Event::KeyReleased: {
                        switch (event.key.code) {
                            case sf::Keyboard::Enter: {
                                map.restart();
                                break;
                            }
                        }
                        break;
                    }
                    case sf::Event::MouseButtonReleased:{
                        switch(event.mouseButton.button){
                            case sf::Mouse::Left:{
                                map.open_cell(mouse_cell_x, mouse_cell_y);
                                break;
                            }
                            case sf::Mouse::Right:{
                                map.flag_cell(mouse_cell_x, mouse_cell_y);
                                break;
                            }
                        }
                    }
                }
            }

            if(gbl::FRAME_DURATION > lag){
                window.clear();
                map.draw(window);
                window.display();
            }
        }
    }

    return 0;
}
