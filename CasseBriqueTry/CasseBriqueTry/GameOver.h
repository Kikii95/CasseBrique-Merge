#pragma once
#include <SFML/Graphics.hpp>
<<<<<<< HEAD
=======
#include <vector>
>>>>>>> Eric
#include "MainMenu.h"

class GameOver : public MainMenu {
public:
    GameOver(sf::RenderWindow& window);
    void display();
    bool handleEvent(sf::Event& event);

<<<<<<< HEAD
=======
    void moveUp();
    void moveDown();
    void select();
    int getSelectedItemIndex() const;


>>>>>>> Eric
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text bricksRemainingText;
    sf::Text bonusText;
    sf::Text scoreText;
    sf::RectangleShape overlay;
<<<<<<< HEAD
=======
    sf::Text replayButton;    // Nouveau bouton
    sf::Text optionsButton;   // Nouveau bouton
    sf::Text quitButton;
    std::vector<sf::Text> menuItems; // Nouveau vecteur pour stocker les éléments de menu
    int selectedItemIndex = 0;
    
>>>>>>> Eric
};
