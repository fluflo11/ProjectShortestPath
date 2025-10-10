#include "grid.hpp"
#include "dijkstra.hpp"
#include <iostream>
#include <vector>
#include <tuple>

//Display Include :
#include "front/main_display.hpp"
#include <windows.h>

int main() {
    try {
        Grid g(5, 5, 0, 0, 4, 4);
        g.setCell(2,2,1);

        std::cout << "Grid:\n";
        g.print();

        Dijkstra solver;
        auto path = solver.findPath(g);

        std::cout << "\nDijkstra's path :\n";
        for (auto [x, y] : path) {
            std::cout << "(" << x << "," << y << ") ";
        }
        std::cout << "\n";

        std::cout << "Launching Direct2D window (App test)...\n";

        App app;
        if (FAILED(app.Initialize())) {
            std::cerr << "Failed to initialize App (Direct2D window)." << std::endl;
            return -1;
        }

        // Boucle principale de messages (ouvre la fenêtre)
        app.RunMessageLoop();

    
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
