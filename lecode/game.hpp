#ifndef GAME_HPP
#define GAME_HPP

#pragma once
#include <iostream>

class Hero {
public:
    int x, y;
    int life;
    int health;

    Hero(int x, int y, int life, int health);
    void move(char direction, int max_rows, int max_cols);
    void teleport(int max_rows, int max_cols);
};

class Game {
private:
    int rows;
    int columns;
    std::vector<char> board;
    Hero hero;  // L'instance du héros
    std::string message;

public: 
    Game(int rows, int columns);
    void play_game();
    void reset_board();
    void add_hero_to_board();
    void teleport_hero();
    void draw_action();
    void draw_board();
    int random(int n);
};

#endif