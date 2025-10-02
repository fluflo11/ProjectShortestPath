#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <tuple>

enum class Move {
    LEFT,RIGHT,UP,DOWN,
    LEFT_UP,LEFT_DOWN,RIGHT_UP,RIGHT_DOWN
};

/**
 * A grid representing a map. Each cell is a node, and from 
 * each node you can move to an adjacent node with a Move (e.g. Move enum).
 */
class Grid{
private:
    int width;
    int height;
    std::tuple<int,int> start;
    std::tuple<int,int> end;
    std::vector<std::vector<int>> cells;

public :
    /**
     * Initialises an empty map
     */
    Grid(int width, int height);
    /**
     * Initialises an empty map with a start and a end
     */
    Grid(int width, int height, int start_x, int start_y, int end_x, int end_y);

    //Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::tuple<int,int> getStart() const { return start; }
    std::tuple<int,int>    getEnd() const { return end; }

    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);
    int moveCost(int x, int y, Move move) const;
    //Debug
    void print() const;
};

#endif //GRID_HPP