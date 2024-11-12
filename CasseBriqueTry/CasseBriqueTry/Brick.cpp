#include "Brick.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

std::vector<sf::Texture> Brick::normalTextures;
std::vector<sf::Texture> Brick::damagedTextures;

Brick::Brick(int x, int y, int width, int height)
    : positionx(x), positiony(y), sizex(width), sizey(height), hitsRemaining(2), isDestroyed(false) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    int textureIndex = rand() % normalTextures.size();
    shape.setTexture(&normalTextures[textureIndex]);
}

// Méthode pour obtenir les limites de la brique (nécessaire pour la collision)
sf::FloatRect Brick::getBounds() const {
    return shape.getGlobalBounds();
}

// Méthode pour vérifier la collision avec une autre forme
bool Brick::checkCollision(const sf::Shape& other) {
    return shape.getGlobalBounds().intersects(other.getGlobalBounds());
}

// Détruit la brique
void Brick::destroy() {
    isDestroyed = true;
}

// Vérifie si la brique est cassée
bool Brick::isBroken() const {
    return isDestroyed;
}

// Accesseurs pour les positions et tailles de la brique
int Brick::getPositionX() const {
    return positionx;
}

int Brick::getPositionY() const {
    return positiony;
}

int Brick::getSizeX() const {
    return sizex;
}

int Brick::getSizeY() const {
    return sizey;
}

// Retourne la forme de la brique
const sf::RectangleShape& Brick::getShape() const {
    return shape;
}

// Charge les textures des briques
void Brick::loadTextures() {
    normalTextures.clear();
    damagedTextures.clear();

    for (int i = 1; i <= 10; ++i) {
        sf::Texture texture, damagedTexture;
        std::string indexStr = (i < 10) ? "0" + std::to_string(i) : std::to_string(i);

        if (texture.loadFromFile(indexStr + "-Breakout-Tiles.png")) {
            normalTextures.push_back(texture);
        }

        if (damagedTexture.loadFromFile(indexStr + "B-Breakout-Tiles.png")) {
            damagedTextures.push_back(damagedTexture);
        }
    }
}

void Brick::takeHit() {
    if (--hitsRemaining == 1) {
        int textureIndex = rand() % damagedTextures.size();
        shape.setTexture(&damagedTextures[textureIndex]);
    }
    if (hitsRemaining <= 0) {
        destroy();
    }
}

//void Brick::takeHit() {
//    hitsRemaining--;
//
//    if (hitsRemaining == 1) {
//        // Passe � la texture endommag�e apr�s le premier coup
//        int textureIndex = -1;
//        for (size_t i = 0; i < normalTextures.size(); ++i) {
//            if (&normalTextures[i] == shape.getTexture()) { // Compare les adresses des textures
//                textureIndex = i;
//                break;
//            }
//        }
//        if (textureIndex != -1) {
//            shape.setTexture(&damagedTextures[textureIndex]);
//        }
//    }
//}
