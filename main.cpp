#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

const sf::Vector2i WINDOW_SIZE(500, 282);
const bool VSYNC = false;
const int TICK_SPEED = 100;
const int DEATH_TH = 128;
const unsigned int SEED = NULL;
const bool SHOW_PATH = false;


void FillGrid(std::vector<sf::Uint8>& grid, sf::Color color = sf::Color::Black) {
    for (int y = 0; y < WINDOW_SIZE.y; y++) {
        for ( int x = 0; x < WINDOW_SIZE.x; x++) {
            grid[(x + y * WINDOW_SIZE.x) * 4 + 0] = color.r;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 1] = color.g;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 2] = color.b;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 3] = color.a;
        }
    }
}

void RandomFill(std::vector<sf::Uint8>& grid) {
    sf::Color color = sf::Color::Black;
    for (int y = 0; y < WINDOW_SIZE.y; y++) {
        for ( int x = 0; x < WINDOW_SIZE.x; x++) {

            bool isAlive = rand() % 11 == 0 ? true : false;

            color = isAlive ? sf::Color::White : sf::Color::Black;

            grid[(x + y * WINDOW_SIZE.x) * 4 + 0] = color.r;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 1] = color.g;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 2] = color.b;
            grid[(x + y * WINDOW_SIZE.x) * 4 + 3] = color.a;
        }
    }
}

void SetPixel(int x, int y, sf::Color color, std::vector<sf::Uint8>& grid) {
    grid[(x + y * WINDOW_SIZE.x) * 4 + 0] = color.r;
    grid[(x + y * WINDOW_SIZE.x) * 4 + 1] = color.g;
    grid[(x + y * WINDOW_SIZE.x) * 4 + 2] = color.b;
    grid[(x + y * WINDOW_SIZE.x) * 4 + 3] = color.a;
}

bool GetCell(int x, int y, std::vector<sf::Uint8>& grid) {
    int n_x = x < 0 ? WINDOW_SIZE.x-1 : x;
    n_x = x >= WINDOW_SIZE.x ? 0 : n_x;

    int n_y = y < 0 ? WINDOW_SIZE.y-1 : y;
    n_y = y >= WINDOW_SIZE.y ? 0 : n_y;

    if (grid[(n_x + n_y * WINDOW_SIZE.x) * 4 + 0] > DEATH_TH) return true;
    return false;
}

void SetupOne(std::vector<sf::Uint8>& grid) {
    // Block
    SetPixel(100, 100, sf::Color::White, grid);
    SetPixel(101, 100, sf::Color::White, grid);
    SetPixel(100, 101, sf::Color::White, grid);
    SetPixel(101, 101, sf::Color::White, grid);

    // Bee-hive
    SetPixel(150, 150, sf::Color::White, grid);
    SetPixel(151, 149, sf::Color::White, grid);
    SetPixel(152, 149, sf::Color::White, grid);
    SetPixel(151, 151, sf::Color::White, grid);
    SetPixel(152, 151, sf::Color::White, grid);
    SetPixel(153, 150, sf::Color::White, grid);

    // Loaf
    SetPixel(101, 150, sf::Color::White, grid);
    SetPixel(102, 150, sf::Color::White, grid);
    SetPixel(100, 151, sf::Color::White, grid);
    SetPixel(101, 152, sf::Color::White, grid);
    SetPixel(102, 153, sf::Color::White, grid);
    SetPixel(103, 151, sf::Color::White, grid);
    SetPixel(103, 152, sf::Color::White, grid);

    // Loaf
    SetPixel(150, 100, sf::Color::White, grid);
    SetPixel(151, 100, sf::Color::White, grid);
    SetPixel(152, 101, sf::Color::White, grid);
    SetPixel(150, 101, sf::Color::White, grid);
    SetPixel(151, 102, sf::Color::White, grid);

    // Blinker
    SetPixel(100, 200, sf::Color::White, grid);
    SetPixel(100, 201, sf::Color::White, grid);
    SetPixel(100, 202, sf::Color::White, grid);

    // Toad
    SetPixel(150, 201, sf::Color::White, grid);
    SetPixel(151, 201, sf::Color::White, grid);
    SetPixel(152, 201, sf::Color::White, grid);
    SetPixel(151, 200, sf::Color::White, grid);
    SetPixel(152, 200, sf::Color::White, grid);
    SetPixel(153, 200, sf::Color::White, grid);

    // Penta-decathlon
    SetPixel(200, 200, sf::Color::White, grid);
    SetPixel(200, 201, sf::Color::White, grid);
    SetPixel(199, 202, sf::Color::White, grid);
    SetPixel(201, 202, sf::Color::White, grid);
    SetPixel(200, 203, sf::Color::White, grid);
    SetPixel(200, 204, sf::Color::White, grid);
    SetPixel(200, 205, sf::Color::White, grid);
    SetPixel(200, 206, sf::Color::White, grid);
    SetPixel(199, 207, sf::Color::White, grid);
    SetPixel(201, 207, sf::Color::White, grid);
    SetPixel(200, 208, sf::Color::White, grid);
    SetPixel(200, 209, sf::Color::White, grid);
}

void GliderGun(int x, int y, std::vector<sf::Uint8>& grid) {

    // block left
    SetPixel(x + 0, y + 4, sf::Color::White, grid);
    SetPixel(x + 1, y + 4, sf::Color::White, grid);
    SetPixel(x + 0, y + 5, sf::Color::White, grid);
    SetPixel(x + 1, y + 5, sf::Color::White, grid);

    // block right
    SetPixel(x + 34, y + 2, sf::Color::White, grid);
    SetPixel(x + 35, y + 2, sf::Color::White, grid);
    SetPixel(x + 34, y + 3, sf::Color::White, grid);
    SetPixel(x + 35, y + 3, sf::Color::White, grid);

    // thing left
    SetPixel(x + 10, y + 4, sf::Color::White, grid);
    SetPixel(x + 10, y + 5, sf::Color::White, grid);
    SetPixel(x + 10, y + 6, sf::Color::White, grid);

    SetPixel(x + 11, y + 3, sf::Color::White, grid);
    SetPixel(x + 12, y + 2, sf::Color::White, grid);
    SetPixel(x + 13, y + 2, sf::Color::White, grid);

    SetPixel(x + 11, y + 7, sf::Color::White, grid);
    SetPixel(x + 12, y + 8, sf::Color::White, grid);
    SetPixel(x + 13, y + 8, sf::Color::White, grid);

    SetPixel(x + 14, y + 5, sf::Color::White, grid);

    SetPixel(x + 15, y + 3, sf::Color::White, grid);
    SetPixel(x + 16, y + 4, sf::Color::White, grid);
    SetPixel(x + 16, y + 5, sf::Color::White, grid);
    SetPixel(x + 17, y + 5, sf::Color::White, grid);
    SetPixel(x + 16, y + 6, sf::Color::White, grid);
    SetPixel(x + 15, y + 7, sf::Color::White, grid);

    //thing rigth
    SetPixel(x + 20, y + 2, sf::Color::White, grid);
    SetPixel(x + 20, y + 3, sf::Color::White, grid);
    SetPixel(x + 20, y + 4, sf::Color::White, grid);
    SetPixel(x + 21, y + 2, sf::Color::White, grid);
    SetPixel(x + 21, y + 3, sf::Color::White, grid);
    SetPixel(x + 21, y + 4, sf::Color::White, grid);

    SetPixel(x + 22, y + 1, sf::Color::White, grid);
    
    SetPixel(x + 22, y + 5, sf::Color::White, grid);

    SetPixel(x + 24, y + 0, sf::Color::White, grid);
    SetPixel(x + 24, y + 1, sf::Color::White, grid);

    SetPixel(x + 24, y + 5, sf::Color::White, grid);
    SetPixel(x + 24, y + 6, sf::Color::White, grid);
}

int NumberOfNeighbors(int x, int y, std::vector<sf::Uint8>& grid) {
    int neighbors = 0;
    for (int line = -1; line <= 1; line++) {
        for (int column = -1; column <= 1; column++) {
            if (line == 0 && column == 0) continue;
            neighbors += GetCell(x+column, y+line, grid) ? 1 : 0;
        }
    }

    return neighbors;
}

void UpdateCells(std::vector<sf::Uint8> &grid) {
    int neighbours = 0;
    bool isAlive = false;

    std::vector<sf::Vector2i> cells_to_kill;
    std::vector<sf::Vector2i> cells_to_live;

    for (int y = 0; y < WINDOW_SIZE.y; y++) {
        for ( int x = 0; x < WINDOW_SIZE.x; x++) {
            isAlive = GetCell(x, y, grid);
            neighbours = NumberOfNeighbors(x, y, grid);
            
            if (isAlive) {
                if (neighbours < 2) {
                    cells_to_kill.push_back(sf::Vector2i(x, y));
                } else if (neighbours > 3 ) {
                    //SetPixel(x, y, sf::Color::Black, grid);
                    cells_to_kill.push_back(sf::Vector2i(x, y));
                }
            } else if(neighbours == 3) {
                //SetPixel(x, y, sf::Color::White, grid);
                cells_to_live.push_back(sf::Vector2i(x, y));
            }
        }
    }

    sf::Color kill_color = SHOW_PATH ? sf::Color(50, 50, 50) : sf::Color::Black;
    for (int i = 0; i < cells_to_kill.size(); i++) {
        SetPixel(cells_to_kill[i].x, cells_to_kill[i].y, kill_color, grid);
    }
    for (int i = 0; i < cells_to_live.size(); i++) {
        SetPixel(cells_to_live[i].x, cells_to_live[i].y, sf::Color::White, grid);
    }
}

int main() {
    if (SEED == NULL) srand((unsigned) time(NULL));
    else srand(SEED);

    sf::RenderWindow window;
    // create the window with size, title and style
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Window");

    // activates verticalsync
    window.setVerticalSyncEnabled(VSYNC);

    sf::Texture grid_texture = sf::Texture();
    grid_texture.create(WINDOW_SIZE.x, WINDOW_SIZE.y);

    std::vector<sf::Uint8> grid(WINDOW_SIZE.x * WINDOW_SIZE.y * 4);

    //FillGrid(grid);
    RandomFill(grid);

    //SetupOne(grid);
    //GliderGun(10, 10, grid);

    grid_texture.update(&grid[0]);

    sf::Sprite grid_sprite = sf::Sprite(grid_texture);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
                
                default:
                    break;
            }
        }
        

        if (clock.getElapsedTime().asMilliseconds() < TICK_SPEED) continue;
        UpdateCells(grid);

        grid_texture.update(&grid[0]);

        window.clear(sf::Color::Black);

        window.draw(grid_sprite);

        window.display();

        clock.restart();
    }
}