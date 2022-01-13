#include "main.h"

int main() {

    std::vector<Cell> matrix;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Cell cell{false,0};
            matrix.push_back(cell);
        }
    }
    random_fill(matrix, (ROWS * COLUMNS) / 10);

    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Conway's Game of Life");

    sf::Clock clock;
    sf::Time delay = sf::seconds(DELAY);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }  //

        sf::Time time = clock.getElapsedTime();
        if (time >= delay) {
            update(matrix);
            clock.restart();
        }

        window.clear(sf::Color::Black);
        draw_matrix(matrix, window);
        window.display();

    }
    return 0;
}

void draw_matrix(std::vector<Cell> &matrix, sf::RenderWindow &window) {

    sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            if (matrix[i * COLUMNS + j].state) {
                cell.setFillColor(sf::Color::White);
            }
            else {
                cell.setFillColor(sf::Color::Black);
            }
            cell.setPosition(i * SIZE, j * SIZE);
            window.draw(cell);

        }
    }

}

void random_fill(std::vector<Cell> &matrix, int N) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {

        int row = rand() % ROWS;
        int col = rand() % COLUMNS;

        while (matrix[row * COLUMNS + col].state) {
            row = rand() % ROWS;
            col = rand() % COLUMNS;
        }

        matrix[row * COLUMNS + col].state = true;

    }

}

void update(std::vector<Cell> &matrix) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            matrix[i * COLUMNS + j].neighbours = 0;

            for (int r = -1; r < 2; r++) {
                for (int c = -1; c < 2; c++) {

                    if ((r == 0 && c == 0) || i + r < 0 || i + r >= ROWS || j + c < 0 || j + c >= COLUMNS) {
                        continue;
                    }

                    if (matrix[(i + r) * COLUMNS + (j + c)].state) {
                        matrix[i * COLUMNS + j].neighbours++;
                    }

                }
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            if (matrix[i * COLUMNS + j].state) {

                if (!(matrix[i * COLUMNS + j].neighbours == 2 || matrix[i * COLUMNS + j].neighbours == 3)) {
                    matrix[i * COLUMNS + j].state = false;
                }

            }
            else {

                if (matrix[i * COLUMNS + j].neighbours == 3) {
                    matrix[i * COLUMNS + j].state = true;
                }

            }

        }
    }

}