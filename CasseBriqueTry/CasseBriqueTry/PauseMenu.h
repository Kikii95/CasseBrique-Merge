#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class PauseMenu
{
public:
    PauseMenu(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
    void selectItemByMouse(sf::Vector2f& mousepos);
    void display(sf::RenderWindow& window);
    void playClickSound();
    ~PauseMenu();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text PauseText;
    sf::RectangleShape overlay;
    std::vector<sf::Text> menuItem;
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RenderWindow& window;
};
