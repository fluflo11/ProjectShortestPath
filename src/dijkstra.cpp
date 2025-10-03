#include "dijkstra.hpp"
#include "grid.hpp"
#include "utils.hpp"  
#include <vector>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <map>
#include <limits>
#include <algorithm>
//TODO : move allMoves in utils.hpp


/**
 * Dijkstra's algorithm implemented on a Grid. The implementation is based on the
 * Wikipedia's pseudocode here : https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 * (Priority Queue version)
 */
std::vector<Coord> Dijkstra::findPath(const Grid& grid) const {
    //Initialisation step
    auto[start_x,start_y] = grid.getStart();
    auto[end_x,end_y] = grid.getEnd();
    int width = grid.getWidth();
    int height = grid.getHeight();
    std::vector<std::vector<int>> distances(height, 
                                            std::vector<int>(width, 
                                                std::numeric_limits<int>::max()
                                            )
                                            );
    std::vector<std::vector<Coord>> previous(height,
                                            std::vector<Coord>(width,{-1,-1})
                                            );
    std::priority_queue<Node,std::vector<Node>,std::greater<Node>> priority_queue;
    distances[start_y][start_x] = 0;
    priority_queue.push({0,{start_x,start_y}});


    while(!priority_queue.empty()){
        Node current = priority_queue.top();
        priority_queue.pop();

        auto[current_x,current_y] = current.coord;

        if(current_x == end_x && current_y == end_y) { 
            break; //End Case
        }

        if(current.dist > distances[current_y][current_x]){
            continue; //Skip of the node has already been visited
        }

        for(auto move : allMoves){
            int cost = grid.moveCost(current_x,current_y,move);
            
            if(cost == -1 ) {
                continue; //Cant do this move
            }

            auto[next_x, next_y] = Dijkstra::move(move, current_x, current_y);
            
            if(!(grid.isNodeAccessible(next_x,next_y))){
                continue;
            }

            int next_distance = distances[current_y][current_x] + cost;
            
            if (next_distance < distances[next_y][next_x]){
                distances[next_y][next_x] = next_distance;
                previous[next_y][next_x] = {current_x,current_y};
                priority_queue.push({next_distance, {next_x,next_y}});
            }

        }
    }

    std::vector<Coord> path;
    int current_x = end_x;
    int current_y = end_y;  
    
    if(previous[current_y][current_x] == Coord{-1,-1} 
    && !(current_x==start_x && current_y==start_y)) {
        return path; //No existing path in the grid
    }

    while (!(current_x == -1 && current_y == -1)) {
    path.push_back({current_x, current_y});
    auto [px, py] = previous[current_y][current_x];
    current_x = px;
    current_y = py;
    }
    std::reverse(path.begin(), path.end());

    return path;
}


