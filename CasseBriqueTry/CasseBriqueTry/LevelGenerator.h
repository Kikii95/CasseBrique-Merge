#pragma once
<<<<<<< HEAD

#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "json.hpp" // Pour la gestion JSON

using json = nlohmann::json;
=======
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Brick.h"
>>>>>>> Eric

class LevelGenerator {
public:
    LevelGenerator();
<<<<<<< HEAD
    void saveLevel(); // Sauvegarde la disposition en JSON
    void handleMouseClick(const sf::Vector2i& mousePos); // Place une brique sur le quadrillage
    void drawGrid(sf::RenderWindow& window); // Affiche le quadrillage

private:
    std::vector<Brick> bricks;
    const int brickWidth = 120;
    const int brickHeight = 40;

    std::pair<int, int> getGridPosition(const sf::Vector2i& mousePos); // Calcule la position dans la grille
=======

    // Méthode pour ajouter une brique au niveau actuel
    void addBrick(int x, int y, int width, int height);

    // Sauvegarder le niveau dans un fichier
    void saveLevel();

    // Charger le prochain numéro de niveau disponible
    int getNextLevelNumber() ;

private:
    std::vector<Brick> bricks;
    int levelNumber;

    // Génère le nom de fichier basé sur le numéro de niveau
    std::string generateLevelFileName(int levelNum) ;
>>>>>>> Eric
};
