#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Brick {
public:
    Brick(int x, int y, int width, int height);

    void takeHit();                     // G�re les coups re�us par la brique
    bool isBroken() const;              // V�rifie si la brique est compl�tement cass�e
    const sf::RectangleShape& getShape() const;
    static void loadTextures();         // Charge toutes les textures au d�marrage

    bool checkCollision(const sf::Shape& other); // V�rifie la collision avec un objet g�n�rique
    void destroy();                     // Marque la brique comme cass�e

    // M�thodes pour obtenir la position et la taille
    float getPositionX() const;
    float getPositionY() const;
    float getSizeX() const;
    float getSizeY() const;

    bool isDestroyed() const; // Ajoute cette m�thode pour v�rifier si la brique est compl�tement d�truite




private:
    sf::RectangleShape shape;
    int hitsRemaining; // Nombre de coups restants pour d�truire la brique

    static std::vector<sf::Texture> normalTextures;
    static std::vector<sf::Texture> damagedTextures;
};
