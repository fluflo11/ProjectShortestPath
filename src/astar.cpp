#include "astar.hpp"
#include "grid.hpp"
#include "utils.hpp" 
#include <vector>
#include <tuple>
#include <cmath>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

struct AStarNode {
    int f; // f = g + h
    Coord coord;

    bool operator>(const AStarNode& other) const {
        return f > other.f;
    }
};


int heuristic(int x1, int y1, int x2, int y2) {
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

std::vector<Coord> AStar::findPath(const Grid& grid) const {
    auto [start_x, start_y] = grid.getStart();
    auto [end_x, end_y] = grid.getEnd();
    int width = grid.getWidth();
    int height = grid.getHeight();

    std::vector<std::vector<int>> g_score(height, 
                                          std::vector<int>(width, std::numeric_limits<int>::max()));
    
    std::vector<std::vector<Coord>> previous(height,
                                             std::vector<Coord>(width, {-1, -1}));

    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> open_set;

    g_score[start_y][start_x] = 0;
    int start_f = heuristic(start_x, start_y, end_x, end_y);
    open_set.push({start_f, {start_x, start_y}});

    while (!open_set.empty()) {
        AStarNode current = open_set.top();
        open_set.pop();

        auto [current_x, current_y] = current.coord;

        if (current_x == end_x && current_y == end_y) {
            break;
        }

        if (current.f > g_score[current_y][current_x] + heuristic(current_x, current_y, end_x, end_y)) {
           continue; 
        }

        for (auto move : allMoves) {
            int movement_cost = grid.moveCost(current_x, current_y, move);
            
            if (movement_cost == -1) {
                continue;
            }
            
            auto [next_x, next_y] = Agent::move(move, current_x, current_y);

            if (!grid.isNodeAccessible(next_x, next_y)) {
                continue;
            }

            int tentative_g = g_score[current_y][current_x] + movement_cost;

            if (tentative_g < g_score[next_y][next_x]) {
                g_score[next_y][next_x] = tentative_g;
                int f_new = tentative_g + heuristic(next_x, next_y, end_x, end_y);
                
                previous[next_y][next_x] = {current_x, current_y};
                open_set.push({f_new, {next_x, next_y}});
            }
        }
    }

    std::vector<Coord> path;
    int cx = end_x;
    int cy = end_y;

    if (previous[cy][cx] == Coord{-1, -1} && !(cx == start_x && cy == start_y)) {
        return path;
    }

    while (!(cx == -1 && cy == -1)) {
        path.push_back({cx, cy});
        auto [px, py] = previous[cy][cx];
        cx = px;
        cy = py;
    }

    std::reverse(path.begin(), path.end());
    return path;
}