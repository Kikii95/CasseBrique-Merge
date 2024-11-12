#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "LevelGenerator.h"
#include "HUD.h"
#include "Pad.h"
#include "Ball.h"
#include "Brick.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include <cstdlib>  
#include <ctime>   
#include "LevelManager.h"
#include <memory>
#include "PadEffect.h"
#include "BallEffect.h"
#include <functional>
#include "Music.h"
#include "LevelManager.h"
#include "OptionsMenu.h"


#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Game {
public:
    Game();
    void run();

    std::vector<std::unique_ptr<BallEffect>> activeBallEffects;
    void applyEffect(int effectIndex);
    bool isVictory = false;
    void resetBall();

protected: 
    sf::RenderWindow window;
    HUD hud;
    Pad pad;
    bool isOptionsMenuActive;
    bool isGameActive = false;
    bool isMainMenuActive;
    bool isPaused;
    Ball ball;
    std::vector<Brick> bricks;
    int score = 0; 
    int bonusCount = 0; 
    std::vector<sf::Sprite> hearts; 
    sf::Texture heartTexture; 
    sf::Texture heartLostTexture; 
    bool isGameOver;
    


private:
    void restartGame();
    void loadBrickTexture();
    void initializeLevelManager();
    void initializeMusic();
    void update(float deltaTime);
    void createInitialBricks(int rows, int columns, int brickWidth, int brickHeight);
    void checkVictoryCondition();
    void render();
    void loadBricksFromJson();
    void updateLevelEditor();
    void saveLevel();
    int getNextLevelNumber() ;

    int lives = 3;
    bool isBallLaunched = false;
    
    bool isLevelEditorActive = false;
    sf::RectangleShape padShape;
    sf::Clock clock;
    Music music;
    GameOver gameOverScreen;
    sf::Event event;
    LevelManager levelManager;
    EndMenu endMenu;
    sf::Shader backgroundShader;
    sf::RectangleShape background;
    std::vector<Ball> activeBalls;
    LevelGenerator levelGenerator;
    void checkLife();
    OptionsMenu* optionsMenu;
    bool isVolumeChanged;
    bool isResolutionChanged;
    float volume; // Volume initial
    int resolutionWidth;
    int resolutionHeight;
    void processEvents();

};
