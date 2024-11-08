#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

<<<<<<< HEAD
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

    sf::RectangleShape getShape();
    sf::FloatRect getBounds() const;

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
=======
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

class Brick {
private:
    bool isDestroyed = false;
    static sf::Texture brickTexture;
    sf::RectangleShape shape;
    int positionx;
    int positiony;
    int sizex;
    int sizey;

public:
    Brick(int x, int y, int sx, int sy);

    void destroy();
    bool isBroken() ;

    static void loadTexture(const std::string& textureFile); 
    static std::vector<Brick> createBricks(int rows, int columns, int brickWidth, int brickHeight);

    sf::RectangleShape getShape() ;

    int getPositionX();
    int getPositionY();
    int getSizeX();
    int getSizeY();

    bool checkCollision(sf::CircleShape& ballShape);
>>>>>>> Eric
};
