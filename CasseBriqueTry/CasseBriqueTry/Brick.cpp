<<<<<<< HEAD
#include "Brick.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Initialisation des textures statiques
std::vector<sf::Texture> Brick::normalTextures;
std::vector<sf::Texture> Brick::damagedTextures;

Brick::Brick(int x, int y, int width, int height)
    : hitsRemaining(2) // Chaque brique n�cessite 2 coups pour �tre cass�e
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    // S�lection al�atoire d'une texture parmi les textures normales
    int textureIndex = rand() % 10;
    shape.setTexture(&normalTextures[textureIndex]);
}

sf::FloatRect Brick::getBounds() const {
    return shape.getGlobalBounds();
}

sf::RectangleShape Brick::getShape() {
    if (isDestroyed()) {
=======
#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include <iostream> 
sf::Texture Brick::brickTexture; 

Brick::Brick(int x, int y, int sx, int sy)
    : positionx(x), positiony(y), sizex(sx), sizey(sy), isDestroyed(false) {

     shape.setSize(sf::Vector2f(sizex, sizey));
     shape.setPosition(positionx, positiony);
     shape.setTexture(&brickTexture); }

void Brick::loadTexture(const std::string& textureFile) {
    if (!brickTexture.loadFromFile(textureFile)) {
        std::cerr << "Erreur : Impossible de charger la texture de la brique depuis " << textureFile << std::endl;
    }
}

void Brick::destroy() { isDestroyed = true; }
bool Brick::isBroken() { return isDestroyed; }

int Brick::getPositionX() { return positionx; }
int Brick::getPositionY() { return positiony; }
int Brick::getSizeX() { return sizex; }
int Brick::getSizeY() { return sizey; }


std::vector<Brick> Brick::createBricks(int rows, int columns, int brickWidth, int brickHeight) {
    std::vector<Brick> bricks;
    std::pair<int, int> spaceBetween = { brickWidth / 2, brickHeight };
    int totalWidth = columns * brickWidth + (columns - 1) * spaceBetween.first;
    int startX = (SCREEN_WIDTH - totalWidth) / 2;
    int topOffset = 150;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int xPos = startX + j * (brickWidth + spaceBetween.first);
            int yPos = topOffset + i * (brickHeight + spaceBetween.second);
            bricks.emplace_back(xPos, yPos, brickWidth, brickHeight);
        }
    }
    return bricks;
}


sf::RectangleShape Brick::getShape()  {
    if (isDestroyed) {
>>>>>>> Eric
        return sf::RectangleShape();
    }
    return shape;
}

<<<<<<< HEAD
// Charge les textures des briques (normales et endommag�es)
void Brick::loadTextures() {
    normalTextures.clear();
    damagedTextures.clear();

    for (int i = 1; i <= 10; ++i) {  // Charge les dix textures disponibles
        std::string indexStr = (i < 10) ? "0" + std::to_string(i) : std::to_string(i);

        sf::Texture texture;
        if (!texture.loadFromFile(indexStr + "-Breakout-Tiles.png")) {
            std::cerr << "Erreur de chargement de la texture " << indexStr << "-Breakout-Tiles.png" << std::endl;
        }
        normalTextures.push_back(texture);

        sf::Texture damagedTexture;
        if (!damagedTexture.loadFromFile(indexStr + "B-Breakout-Tiles.png")) {
            std::cerr << "Erreur de chargement de la texture " << indexStr << "B-Breakout-Tiles.png" << std::endl;
        }
        damagedTextures.push_back(damagedTexture);
    }
}

// Fonction pour g�rer les coups re�us par la brique
void Brick::takeHit() {
    hitsRemaining--;

    if (hitsRemaining == 1) {
        // Passe � la texture endommag�e apr�s le premier coup
        int textureIndex = -1;
        for (size_t i = 0; i < normalTextures.size(); ++i) {
            if (&normalTextures[i] == shape.getTexture()) { // Compare les adresses des textures
                textureIndex = i;
                break;
            }
        }
        if (textureIndex != -1) {
            shape.setTexture(&damagedTextures[textureIndex]);
        }
    }
}

bool Brick::isBroken() const {
    return hitsRemaining <= 0;
}

const sf::RectangleShape& Brick::getShape() const {
    return shape;
}

bool Brick::isDestroyed() const {
    return hitsRemaining <= 0;
}


// M�thodes pour obtenir la position et la taille de la brique
float Brick::getPositionX() const {
    return shape.getPosition().x;
}

float Brick::getPositionY() const {
    return shape.getPosition().y;
}

float Brick::getSizeX() const {
    return shape.getSize().x;
}

float Brick::getSizeY() const {
    return shape.getSize().y;
}

// V�rifie la collision entre la brique et un autre objet
bool Brick::checkCollision(const sf::Shape& other) {
    return shape.getGlobalBounds().intersects(other.getGlobalBounds());
}
// Marque la brique comme cass�e
void Brick::destroy() {
    hitsRemaining = 0; // Marque la brique comme cass�e
=======
bool Brick::checkCollision(sf::CircleShape& ballShape) {
    if (isDestroyed) return false;

    sf::RectangleShape brickShape(sf::Vector2f(sizex, sizey));
    brickShape.setPosition(positionx, positiony);

    return ballShape.getGlobalBounds().intersects(brickShape.getGlobalBounds());
>>>>>>> Eric
}
