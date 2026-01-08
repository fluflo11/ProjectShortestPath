#include "grid.hpp"
#include "dijkstra.hpp" // Suppose que tu as ces fichiers
#include "astar.hpp"
#include "main_display.hpp" // Ton fichier modifié
#include <iostream>

int main() {
    // 1. Initialisation de la logique
    Grid g(10, 10, 0, 0, 9, 9); // Une grille 10x10
    
    // Ajout d'obstacles pour tester l'affichage noir
    g.setCell(4, 4, Grid::BLOCKED);
    g.setCell(4, 5, Grid::BLOCKED);
    g.setCell(4, 6, Grid::BLOCKED);

    // 2. Résolution
    // (Choisis le solver que tu veux afficher)
    AStar solver;
    auto path = solver.findPath(g);

    std::cout << "Path found with size: " << path.size() << std::endl;

    // 3. Interface Graphique (Direct2D)
    App app;
    
    // Initialisation de la fenêtre
    if (FAILED(app.Initialize())) {
        std::cerr << "Failed to initialize App." << std::endl;
        return -1;
    }

    // --- C'est ici qu'on fait le lien ---
    // On envoie l'adresse de la grille et le chemin calculé à l'App
    app.SetData(&g, path); 

    std::cout << "Displaying window..." << std::endl;
    
    // Lancement de la boucle d'affichage
    app.RunMessageLoop();

    return 0;
}