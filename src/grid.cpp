#include "grid.hpp"

Grid::Grid(int width, int height) : width(width), height(height){
     cells = std::vector<std::vector<int>>(height,
                            std::vector<int>(width,0));
}

Grid::Grid(int width, int height, 
        int start_x, int start_y, 
        int end_x, int end_y): width(width), height(height){

    if (start_x < 0 || start_x >= width || start_y < 0 || start_y >= height) {
        throw std::out_of_range("Starting cell coordinates are out of range");
    }
    if (end_x < 0 || end_x >= width || end_y < 0 || end_y >= height) {
        throw std::out_of_range("Ending cell coordinates are out of range");
    }

    start = std::make_tuple(start_x, start_y);
    end = std::make_tuple(end_x, end_y);

    cells = std::vector<std::vector<int>>(height,
                            std::vector<int>(width,0));
}


int Grid::getCell(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Cell coordinates are out of range");
    }
    return cells[y][x];
}

void Grid::setCell(int x, int y, int value){
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Cell coordinates are out of range");
    }
    
    cells[x][y] = value;
}

/**
 * Compte the cost of a move on the grid.
 */
int Grid::moveCost(int x, int y, Move move){
    int nextX = x;
    int nextY = y;
    int cost = -1;

    switch(move){
        case Move::LEFT: 
            nextX--; 
            cost = 10;
            break;
        case Move::RIGHT: 
            nextX++; 
            cost = 10;
            break;
        case Move::UP: 
            nextY--;
            cost = 10; 
            break;
        case Move::DOWN: 
            nextY++; 
            cost = 10;
            break;
        case Move::LEFT_UP:    
            nextX--; nextY--;
            cost = 14;
            break;
        case Move::LEFT_DOWN:  
            nextX--; nextY++;
            cost = 14; 
            break;
        case Move::RIGHT_UP:   
            nextX++; nextY--;
            cost = 14; 
            break;
        case Move::RIGHT_DOWN: 
            nextX++; nextY++;
            cost = 14; 
            break;
    }

    if(nextX <0 || nextX >= width || nextY <0 || nextY >= height){
        return -1;
    }

    return cost;
}

void Grid::print() const {
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            std::cout << cells[x][y] << " ";
        }
        std::cout << "\n";
    }
}