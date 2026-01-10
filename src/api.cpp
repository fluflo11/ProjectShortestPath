#ifndef API_HPP
#define API_HPP

#include "grid.hpp"
#include "agent.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"
#include <iostream>
#include <emscripten/bind.h>


using namespace emscripten;

struct Point{
    int x;
    int y;
};

class PathFinding{
    private: 
        Grid grid;
    public:
        PathFinding(int w, int h):grid(w,h){}
        void addObstacle(int x, int y){
            grid.setCell(x,y,Grid::BLOCKED);
        }
        void clearObstacles(int w, int h){
            grid = Grid(w,h,0,0,w-1,h-1);
        }   
        /**
         * A function that includes findpath of every algorithm/agent to make it easier to use in html.
         */
        std::vector<Point> findPath(std::string agent){
            std::vector<std::tuple<int,int>> path;
            if(agent == "dijkstra"){
                Dijkstra algo;
                path = algo.findPath(grid);
            }
            else if(agent == "astar"){
                AStar algo;
                path = algo.findPath(grid);
            }
            else{
                throw std::invalid_argument("\"" + agent + "\" doesnt exist");
            }

            std::vector<Point> jsPath;//easier to exploit in js
            for(const auto&[x,y]:path){
                jsPath.push_back({x,y});
            }
            return jsPath;
        }
};

/**
 * Binding to compile it to js 
 */
EMSCRIPTEN_BINDINGS(api_module){
    value_object<Point>("Point")
        .field("x",&Point::x)
        .field("y",&Point::y);

    class_<PathFinding>("PathFinding")
        .constructor<int,int>()
        .function("addObstacle",&PathFinding::addObstacle)
        .function("clearObstacles",&PathFinding::clearObstacles)
        .function("findPath",&PathFinding::findPath);

    register_vector<Point>("VectorPoint");
};



#endif