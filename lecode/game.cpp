#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "game.hpp"
#include "keyboard_event.hpp"

// Ceci est le squelette d'un jeu où un caractère se déplace sur un board.
// Le code est ici volontairement très simple, moche et pas structuré du tout (des variables globales !)
// Tout ceci devra naturellement être repensé, étendu, organisé en classes...

// MESSAGE
// pour parler au joueur
std::string message = "Welcome to our super game !";


Game::Game(int r, int c) : rows(r), columns(c), hero(2, 7, 3, 20) {
    rows = r;
    columns = c;
    renderer = new SDLRenderer(1180, 150, 10);
    dungeon.push_back("######################################################################################################################");
    dungeon.push_back("#............##............#############################.............................................................#");
    dungeon.push_back("#............##............#########################+++++####..##############################################.########");
    dungeon.push_back("#....#####...##..#.###.....########################++#########.###########..........................#########.########");
    dungeon.push_back("#....#...#.......#...#.....####################+++++##########....#####....############.###########.#########.########");
    dungeon.push_back("#....#...............#.....####################+#############..##.#####.####....#######.##########..#######...########");
    dungeon.push_back("#....#.###.......#####.....####################+############..###....##.##...##.#######.##########.###################");
    dungeon.push_back("#............##............+++++++++++++++++++++############.#######.##.#..####....###############..##################");
    dungeon.push_back("#............##............#########################################......########.################.........##########");
    dungeon.push_back("###########################################################################################################+##########");
    dungeon.push_back("###########################################################################################################+##########");
    dungeon.push_back("#####################################################################################.........########++++++##########");
    dungeon.push_back("#####################################################################################....@....########+###############");
    dungeon.push_back("#####################################################################################.........+++++++++###############");
    dungeon.push_back("######################################################################################################################");
}


Game::~Game() {
    delete renderer; 
}

void Game::reset_board()
{
    for (int i = 0; i < board.size(); i++)
        board[i] = '.';
}


Hero::Hero(int x, int y, int life, int health) : x(x), y(y), life(life), health(health) {}


// ajouter le hero sur le board
void Game::add_hero_to_board()
{
    // super moche avec ses variables globales
    board.at(hero.x * columns + hero.y) = '@';
}

int Game::random(int n)
// c random generation of a integer between 0 and n.
{
    return rand() % n;
}

void Hero::teleport(int max_rows, int max_cols)
{
    x = rand() % max_rows;
    y = rand() % max_cols;
}

// on téléporte le hero (pour montrer random)
void Game::teleport_hero()
{
    hero.teleport(rows, columns);
    hero.health--; // Le héros se fatigue
}

// AUTRES AFFICHAGES

void Game::draw_action()
{
    std::cout << std::endl
              << std::endl;
    std::cout << "'q' to quit" << std::endl;
    std::cout << "'i' up 'k' down 'l' right 'j' left" << std::endl;
    std::cout << "'t' teleport" << std::endl;
}

// on dessine le board avec les messages
void Game::draw_board()
{
    // message
    std::cout << message << std::endl;

    // board
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
            std::cout << board.at(r * columns + c);
        std::cout << std::endl;
    }

    // état/position du héro
    std::cout << "life: " << hero.life << " health: " << hero.health;
    // ou si on a besoin d'une string
    std::string pos = " position " + std::to_string(hero.x) + ", " + std::to_string(hero.y);
    std::cout << pos << std::endl;
}

void Hero::move(char direction, int max_rows, int max_cols)
{
    if (direction == 'l' && y + 1 < max_cols) y++;
    else if (direction == 'j' && y - 1 >= 0) y--;
    else if (direction == 'i' && x - 1 >= 0) x--;
    else if (direction == 'k' && x + 1 < max_rows) x++;
}


void Game::play_game() {
    char key = 'l';
    bool running = true;

    while (running) {
        reset_board();
        add_hero_to_board();

        // Rendu SDL
        renderer->drawDungeon(board);
        renderer->render();

        if (keyEventBlocking()) {
            std::cin >> key;

            if (key == 'i' || key == 'k' || key == 'j' || key == 'l') {
                hero.move(key, rows, columns);
            } else if (key == 't') {
                teleport_hero();
            } else if (key == 'q') {
                running = false;
            }
            hero.health--;
        }

        running = renderer->handleEvents();
    }
}

