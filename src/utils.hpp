#ifndef UTILS_HPP
#define UTILS_HPP

#include <tuple>

using Coord = std::tuple<int,int>;

struct Node {
    int dist;
    Coord coord;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};




#endif
