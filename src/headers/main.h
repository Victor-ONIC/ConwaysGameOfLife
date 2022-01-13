#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

// Dimensions du jeu.
constexpr int ROWS = 300;
constexpr int COLUMNS = 180;
constexpr int SIZE = 5;

// Taille de la fenêtre.
constexpr int WIN_WIDTH = ROWS * SIZE;
constexpr int WIN_HEIGHT = COLUMNS * SIZE;

// Secondes entre chaque itérations.
constexpr float DELAY = 0.05f;

struct Cell {
    bool state;
    int neighbours;
};

void draw_matrix(std::vector<Cell> &matrix, sf::RenderWindow &window);
void random_fill(std::vector<Cell> &matrix, int N);
void update(std::vector<Cell> &matrix);