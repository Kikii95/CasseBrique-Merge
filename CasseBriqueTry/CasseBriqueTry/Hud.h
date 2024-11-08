#pragma once
#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include <vector>
#include <iostream>
#include "MainMenu.h"
=======
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "EndMenu.h"
>>>>>>> Eric
#include "PauseMenu.h"

class HUD {
public:
    HUD(int width, int height, sf::RenderWindow& window);
<<<<<<< HEAD
    void draw(sf::RenderWindow& window, bool isMainMenuActive);
    void updateScore(int score);
    void showPauseMenu(bool show);
    void handleMouseClick( sf::Vector2f& mousepos);
    void handleKeyboardInput(sf::Keyboard::Key key);
    int getSelectedMenuIndex();

    MainMenu& getMainMenu() { return mainMenu; } 
    PauseMenu& getPauseMenu() { return pauseMenu; } 
=======

    void draw(sf::RenderWindow& window, bool isMainMenuActive, bool isPaused, bool isGameOver, bool isOptionsMenuActive);
    void handleMouseClick(sf::Vector2f& mousepos);
    void handleKeyboardInput(sf::Keyboard::Key key);
    void updateScore(int score);
    int getSelectedMenuIndex();
    MainMenu& getMainMenu();       // Renvoie une référence
    PauseMenu& getPauseMenu();     // Renvoie une référence
    EndMenu& getEndMenu();         // Renvoie une référence
    OptionsMenu& getOpMenu();      // Renvoie une référence
>>>>>>> Eric

    ~HUD();

private:
<<<<<<< HEAD
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    sf::Text scoreText;
    sf::Font font;
    int score;
    bool isPaused;
=======
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
>>>>>>> Eric
};
