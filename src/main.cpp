#include <grid.hpp>


int main() {
    try {
        // Test constructeur
        Grid g(5, 5, 0, 0, 4, 4);
        std::cout << "Width: " << g.getWidth() << ", Height: " << g.getHeight() << "\n";

        //Tests start et end
        auto [sx, sy] = g.getStart();
        auto [ex, ey] = g.getEnd();
        std::cout << "Start: (" << sx << "," << sy << ")\n";
        std::cout << "End: (" << ex << "," << ey << ")\n";

        // Tests sets
        g.setCell(2, 2, 9);
        g.setCell(1, 3, 5);
        std::cout << "Cell (2,2): " << g.getCell(2, 2) << "\n";
        std::cout << "Cell (1,3): " << g.getCell(1, 3) << "\n";

        // Test print
        std::cout << "Grille:\n";
        g.print();

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}