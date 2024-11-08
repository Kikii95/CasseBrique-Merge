#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class MainMenu
{
public:
	
	
	MainMenu(sf::RenderWindow& window);

	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int getSelectedItemIndex();
	void selectItemByMouse( sf::Vector2f &mousepos);
	void reset();
	void playClickSound();
	sf::Sound& getClickSound();
	~MainMenu();

private:

	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text>menuItem;
	sf::SoundBuffer clickSoundBuffer;
	sf::Sound clickSound;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

};

