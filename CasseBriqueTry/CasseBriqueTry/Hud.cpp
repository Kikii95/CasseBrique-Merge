<<<<<<< HEAD
#include "HUD.h"

HUD::HUD(int width, int height, sf::RenderWindow& window)
    : mainMenu(window), pauseMenu(window), score(0), isPaused()
{
    
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20); 
}

void HUD::draw(sf::RenderWindow& window, bool isMainMenuActive) {
=======
#pragma once
#include "Hud.h"

HUD::HUD(int width, int height, sf::RenderWindow& window)
    : mainMenu(window), pauseMenu(window), endMenu(window),opMenu(window), score(50),
    isPaused(false), isMainMenuActive(true), isGameOver(false), isOptionsMenuActive(false) {
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
    else {
        std::cout << "Police chargée avec succès." << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10, 10);
}

void HUD::draw(sf::RenderWindow& window, bool isMainMenuActive, bool isPaused, bool isGameOver,bool isOptionsMenuActive) {
    
    
>>>>>>> Eric
    window.draw(scoreText);

    if (isMainMenuActive) {
        mainMenu.draw(window);
    }
    else if (isPaused) {
<<<<<<< HEAD
        pauseMenu.draw(window);
=======
        pauseMenu.display(window);
    }
    else if (isGameOver) {
        endMenu.display();
    }
    else if (isOptionsMenuActive) {
        opMenu.display(window);
>>>>>>> Eric
    }
}

void HUD::updateScore(int newScore)
{
<<<<<<< HEAD
    score = newScore;
    scoreText.setString("Score: " + std::to_string(score));
}

void HUD::showPauseMenu(bool show)
{
    isPaused = show;
=======
    // Mettre à jour le score dans l'objet scoreText
    score = newScore;  // Met à jour la variable score
    scoreText.setString("Score : " + std::to_string(score));  // Mets à jour le texte avec le score
    std::cout << "Mise à jour du score : " << score << std::endl;  // Affiche dans la console
>>>>>>> Eric
}

void HUD::handleMouseClick( sf::Vector2f& mousepos)
{
<<<<<<< HEAD
    if (isPaused) {
        pauseMenu.selectItemByMouse(mousepos);
    } else {
        mainMenu.selectItemByMouse(mousepos);
    }
=======
   /* if (isPaused) {
        pauseMenu.selectItemByMouse(mousepos);
    } else {
        mainMenu.selectItemByMouse(mousepos);
    }*/
>>>>>>> Eric
}

void HUD::handleKeyboardInput(sf::Keyboard::Key key)
{
<<<<<<< HEAD
    if (isPaused) {
        if (key == sf::Keyboard::Up) {
            pauseMenu.moveUp();
        } else if (key == sf::Keyboard::Down) {
            pauseMenu.moveDown();
        }
    } else {
        if (key == sf::Keyboard::Up) {
            mainMenu.moveUp();
        } else if (key == sf::Keyboard::Down) {
=======
    
    if (isPaused) {
        // Si le jeu est en pause, g�rer les entr�es du clavier pour le menu de pause
        if (key == sf::Keyboard::Up) {
            pauseMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            pauseMenu.moveDown();
        }
    }
    else if (isGameOver) {
        // Si le jeu est termin�, g�rer les entr�es du clavier pour le menu de fin de jeu
        if (key == sf::Keyboard::Up) {
            endMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            endMenu.moveDown();
        }
    }
    else if (isOptionsMenuActive) {
        // Si le jeu est termin�, g�rer les entr�es du clavier pour le menu de fin de jeu
        if (key == sf::Keyboard::Up) {
            opMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            opMenu.moveDown();
        }
    }
    else  {
        // Si le jeu n'est pas en pause et que le jeu n'est pas termin�, g�rer les entr�es du clavier pour le menu principal
        if (key == sf::Keyboard::Up) {
            mainMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
>>>>>>> Eric
            mainMenu.moveDown();
        }
    }
}

int HUD::getSelectedMenuIndex()
{
<<<<<<< HEAD
    return isPaused ? pauseMenu.getSelectedItemIndex() : mainMenu.getSelectedItemIndex();
}

=======
    if (isPaused) {
        return pauseMenu.getSelectedItemIndex();
    }
    else if (isGameOver) {
  
        return endMenu.getSelectedItemIndex(); // Impl�mentation n�cessaire dans EndMenu
    }
    else if (isOptionsMenuActive) {
        return opMenu.getSelectedItemIndex();
    }
    else {
        return mainMenu.getSelectedItemIndex();
    }
}

MainMenu& HUD::getMainMenu()
{
    return mainMenu;
}

PauseMenu& HUD::getPauseMenu()
{
    return pauseMenu;
}

EndMenu& HUD::getEndMenu()
{
    return endMenu;
}

OptionsMenu& HUD::getOpMenu()
{
    return opMenu;
}



>>>>>>> Eric
HUD::~HUD() {}
