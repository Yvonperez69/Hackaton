#pragma once
class Game {
private:
    int rows; //10
    int columns; //20
    std::vector<char> board; //std::vector<char> board = std::vector<char>(rows * columns, '.');
    void play_game();
    void reset_board();
    void add_hero_to_board();
    void teleport_hero();
    void draw_action();
    void draw_board();
    int random(int n);

public: 
    Game(int rows, int columns);
};

class Hero {
private:
int x,y;
int life,health;

public:
    Hero(int x, int y, int life, int health);
};