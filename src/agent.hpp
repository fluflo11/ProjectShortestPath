#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include "grid.hpp"

/**
 * Abstract class to represent a solving Agent. 
 */
class Agent {
public:
    virtual ~Agent() = default;
    /**
     * Finds the shortest path from the start to the end of the given Grid.
     */
    virtual std::vector<std::tuple<int,int>> findPath(const Grid& grid) const = 0;
    /**
     * Just here to allow an agent to move on the grid. Different
     * from the move cost evaluation function in grid.hpp.
     */
    std::tuple<int,int> move(Move move, int x, int y) const;
};


#endif //ALGORITHMS_H