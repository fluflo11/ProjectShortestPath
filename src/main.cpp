#include "grid.hpp"
#include "dijkstra.hpp"
#include <iostream>
#include <vector>
#include <tuple>

int main() {
    try {
        Grid g(5, 5, 0, 0, 4, 4);
        std::cout << "Grid:\n";
        g.print();

        Dijkstra solver;
        auto path = solver.findPath(g);

        std::cout << "\nDijkstra's path :\n";
        for (auto [x, y] : path) {
            std::cout << "(" << x << "," << y << ") ";
        }
        std::cout << "\n";
    
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
