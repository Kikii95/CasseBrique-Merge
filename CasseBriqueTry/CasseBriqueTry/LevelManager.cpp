#include "LevelManager.h"
<<<<<<< HEAD
#include "Pad.h"
#include "Brick.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann::json;


LevelManager::LevelManager() : currentLevel(LevelType::LEVEL_1) {}

bool LevelManager::selectLevel(sf::RenderWindow& window, LevelType level) {
    currentLevel = level;
    return true;
}

LevelType LevelManager::getCurrentLevel() const {
    return currentLevel;
}

void LevelManager::initializeLevel(LevelType level, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    bricks.clear();

    if (level == LevelType::LEVEL_3) {
        if (!loadLevelFromFile("level_3.lvl", bricks)) {
            std::cerr << "Erreur : impossible de charger le niveau 3 depuis le fichier level_3.lvl" << std::endl;
        }
    }
    else if (level == LevelType::LEVEL_1) {
        // Initialisez les briques pour le niveau 1 ici si n�cessaire
    }

    pad.setPosition(0.8f * SCREEN_WIDTH, 0.9f * SCREEN_HEIGHT);
    ball.setPosition(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize());
    ball.setSpeed(400);
}

bool LevelManager::loadLevelFromFile(const std::string& filename, std::vector<Brick>& bricks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    int posX, posY, sizeX, sizeY;
    while (file >> posX >> posY >> sizeX >> sizeY) {
        bricks.emplace_back(posX, posY, sizeX, sizeY);
    }

    file.close();
    std::cout << "Niveau charg� depuis " << filename << std::endl;
    return true;
}


void LevelManager::renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, const std::vector<Brick>& bricks) {
    // Dessiner le pad et la balle
    window.draw(pad.getShape());  // Cette ligne utilise maintenant getShape() correctement
    window.draw(ball.getShape());

    // Dessiner les briques
    for (const auto& brick : bricks) {
        if (!brick.isBroken()) {  // isBroken() peut maintenant �tre appel�e sur const Brick
            window.draw(brick.getShape());
        }
=======

LevelManager::LevelManager() : selectedOption(0) {}

LevelManager::~LevelManager() {}

int LevelManager::getSelectedOption() {
    return selectedOption;
}

void LevelManager::setSelectedOption(int option) {
    selectedOption = option;
}

bool LevelManager::selectLevel(sf::RenderWindow& window, int option) {
    selectedOption = option;
    sf::Font font;
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police " << std::endl;
        return false;
    }

    sf::Text level1Text("Niveau 1", font, 50);
    level1Text.setPosition(800, 400);

    sf::Text level2Text("Niveau 2", font, 50);
    level2Text.setPosition(800, 500);

    int selectedOption = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedOption = 0;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    selectedOption = 1;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    currentLevel = (selectedOption == 0) ? LevelType::Level1 : LevelType::Level2;
                    return true;
                }
            }
        }

        if (selectedOption == 0) {
            level1Text.setFillColor(sf::Color::Red);
            level2Text.setFillColor(sf::Color::White);
        }
        else {
            level1Text.setFillColor(sf::Color::White);
            level2Text.setFillColor(sf::Color::Red);
        }

        window.clear();
        window.draw(level1Text);
        window.draw(level2Text);
        window.display();
    }

    return false;
}

void LevelManager::initializeLevel(LevelType levelType, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    pad = Pad((0.8 * SCREEN_WIDTH), (0.2 * SCREEN_HEIGHT));
    ball = Ball(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize() / 2, (0.3 * SCREEN_HEIGHT), (0.01 * SCREEN_WIDTH));

    if (levelType == LevelType::Level1) {
        bricks.clear();
        bricks = Brick::createBricks(5, 10, 115, 40);
    }
    else if (levelType == LevelType::Level2) {
        bricks.clear();
        bricks.emplace_back(800, 300, 115, 40);
        bricks.emplace_back(1000, 300, 115, 40);
    }
}

void LevelManager::renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    for (Brick& brick : bricks) {
        if (!brick.isBroken()) window.draw(brick.getShape());
>>>>>>> Eric
    }
}
