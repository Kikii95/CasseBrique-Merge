#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "EndMenu.h"
#include "PauseMenu.h"

class HUD {
public:
    HUD(int width, int height, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, bool isMainMenuActive, bool isPaused, bool isGameOver, bool isOptionsMenuActive);
    void handleMouseClick(sf::Vector2f& mousepos);
    void handleKeyboardInput(sf::Keyboard::Key key);
    void updateScore(int score);
    int getSelectedMenuIndex();
    MainMenu& getMainMenu();       // Renvoie une référence
    PauseMenu& getPauseMenu();     // Renvoie une référence
    EndMenu& getEndMenu();         // Renvoie une référence
    OptionsMenu& getOpMenu();      // Renvoie une référence

    ~HUD();

private:
    MainMenu mainMenu;             // Objets correctement déclarés
    PauseMenu pauseMenu;
    EndMenu endMenu;
    OptionsMenu opMenu;

    sf::Text scoreText;
    sf::Font font;
    int score;                     // Déclaration simple
    bool isPaused;                 // Variables booléennes
    bool isMainMenuActive;
    bool isGameOver;
    bool isOptionsMenuActive;
};
