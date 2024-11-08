#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> 
#include "Ball.h"
#include "Brick.h"

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Pad {
public:
    Pad(float speed, int size);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    static float originalSpeed;
    static std::pair<int, int> originalSize;

    void setSpeed(float newSpeed);
    float getSpeed() ;

    std::pair<float, float> getPosition() ;
    virtual void setPosition(float positionX, float positionY);
    std::pair<int, int> getSize() ;
    virtual void setSize(int size);

    bool isShieldActive;
    
    void displayPosition();

    void setInvertedControls(bool inverted);

protected:
    sf::Texture padTexture;  
    float positionX, positionY;
    float speed;     int sizeX, sizeY;
    sf::RectangleShape getShape() const;  // Modifie pour retourner un Pad avec texture
    bool loadTexture(const std::string& filePath); // Ajoute une m�thode pour charger la texture

};
