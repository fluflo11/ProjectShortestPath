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
    std::vector<std::tuple<int,int>> findPath(Grid grid) const;
};


#endif //ALGORITHMS_HPP