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

std::vector<Move> allMoves = {
    Move::LEFT, Move::RIGHT, Move::UP, Move::DOWN,
    Move::LEFT_UP, Move::LEFT_DOWN, Move::RIGHT_UP, Move::RIGHT_DOWN
};


#endif
