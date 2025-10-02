#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include "agent.hpp"
#include "grid.hpp"

//TODO : Implement dijkstra's algorithm
class Dijkstra: public Agent{
public:
    /**
     * Finds the shortest path from the start to the end of the given Grid, using Dijkstra's
     * algorithm.
     */
    std::vector<std::tuple<int,int>> findPath(const Grid& grid) const override;
    /**
     *
     */
};  



#endif