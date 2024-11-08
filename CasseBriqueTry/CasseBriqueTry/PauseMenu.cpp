#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window), selectedItemIndex(0) {
    overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    sf::Text play("Play", font, 100);
    play.setFillColor(sf::Color::White);
    sf::FloatRect playBounds = play.getLocalBounds();
    play.setOrigin(playBounds.width / 2, playBounds.height / 2);
    play.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300);
    menuItem.push_back(play);

    sf::Text quit("Quit", font, 100);
    quit.setFillColor(sf::Color::White);
    sf::FloatRect quitBounds = quit.getLocalBounds();
    quit.setOrigin(quitBounds.width / 2, quitBounds.height / 2);
    quit.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300);
    menuItem.push_back(quit);

    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {
        std::cerr << "Erreur : impossible de charger le son du clic." << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);
}

void PauseMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(overlay);
    window.draw(PauseText);
    for (const auto& item : menuItem) {
        window.draw(item);
    }
}

void PauseMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void PauseMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItem.size()) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int PauseMenu::getSelectedItemIndex() const {
    return selectedItemIndex;
}

void PauseMenu::selectItemByMouse(sf::Vector2f& mousepos) {
    for (size_t i = 0; i < menuItem.size(); ++i) {
        if (menuItem[i].getGlobalBounds().contains(mousepos)) {
            menuItem[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex = i;
            menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
            break;
        }
    }
}

void PauseMenu::display(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(overlay);
    window.draw(PauseText);
    for (const auto& item : menuItem) {
        window.draw(item);
    }
}

void PauseMenu::playClickSound() {
    clickSound.play();
}

PauseMenu::~PauseMenu() {}
