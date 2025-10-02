#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

enum class Move {
    LEFT,RIGHT,UP,DOWN,
    LEFT_UP,LEFT_DOWN,RIGHT_UP,RIGHT_DOWN
};

class Grid{
private:
    int width;
    int height;
    std::vector<std::vector<int>> cells;

public :
    /**
     * Initialises a 
     */
    Grid(int width, int height);

    //Getters
    int getWidth() const { return width; }
    int getheight() const { return height; }
    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);

    //Debug
    void print() const;
};

#endif //GRID_HPP