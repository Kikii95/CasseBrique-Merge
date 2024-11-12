#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Brick {
public:
    Brick(int x, int y, int width, int height);
    void destroy();
    bool isBroken() const;
    void takeHit();

    // Ajout des méthodes manquantes
    sf::FloatRect getBounds() const;
    bool checkCollision(const sf::Shape& other);

    int getPositionX() const;
    int getPositionY() const;
    int getSizeX() const;
    int getSizeY() const;
    const sf::RectangleShape& getShape() const;
    static void loadTextures();

private:
    int positionx;
    int positiony;
    int sizex;
    int sizey;
    int hitsRemaining = 2;
    bool isDestroyed = false;
    sf::Texture brickTexture;
    sf::RectangleShape shape;
    static std::vector<sf::Texture> normalTextures;
    static std::vector<sf::Texture> damagedTextures;
};
