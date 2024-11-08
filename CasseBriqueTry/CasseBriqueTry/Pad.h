#pragma once
#include <iostream>
<<<<<<< HEAD
#include <SFML/Graphics.hpp> 
#include "Brick.h"

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160
=======
#include <SFML/Graphics.hpp> // Inclure SFML pour utiliser RectangleShape
#include "Ball.h"
#include "Brick.h"

#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440
>>>>>>> Eric

class Pad {
public:
    Pad(float speed, int size);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

<<<<<<< HEAD
    static float originalSpeed;
    static std::pair<int, int> originalSize;

=======
>>>>>>> Eric
    void setSpeed(float newSpeed);
    float getSpeed() ;

    std::pair<float, float> getPosition() ;
    virtual void setPosition(float positionX, float positionY);
    std::pair<int, int> getSize() ;
    virtual void setSize(int size);

<<<<<<< HEAD
    bool isShieldActive;
    
    void displayPosition();
    sf::RectangleShape getShape() const;

    /*void setInvertedControls(bool inverted);*/
    bool loadTexture(const std::string& filePath);

protected:
    sf::Texture padTexture;  
    float positionX, positionY;
    float speed;     int sizeX, sizeY;
    

=======
    void displayPosition();

protected:
    float positionX, positionY;
    float speed;     int sizeX, sizeY;
>>>>>>> Eric
};
