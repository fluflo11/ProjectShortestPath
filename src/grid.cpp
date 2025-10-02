#include "grid.hpp"

Grid::Grid(int width, int height) : width(width), height(height){
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

void Grid::print() const {
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            std::cout << cells[x][y] << " ";
        }
        std::cout << "\n";
    }
}