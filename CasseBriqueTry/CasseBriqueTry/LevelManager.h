#pragma once
<<<<<<< HEAD
#include <vector>
#include <string>
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include "json.hpp" // Inclure la biblioth�que JSON
using json = nlohmann::json;

enum LevelType {
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
=======
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pad.h"
#include "Ball.h"
#include "Brick.h"

enum class LevelType {
    Level1,
    Level2
>>>>>>> Eric
};

class LevelManager {
public:
    LevelManager();
<<<<<<< HEAD
    bool selectLevel(sf::RenderWindow& window, LevelType level);  // S�lectionne le niveau
    void initializeLevel(LevelType level, Pad& pad, Ball& ball, std::vector<Brick>& bricks);
    void renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, const std::vector<Brick>& bricks);
    LevelType getCurrentLevel() const;

private:
    LevelType currentLevel;
    bool loadLevelFromFile(const std::string& filename, std::vector<Brick>& bricks);
=======
    ~LevelManager();

    int selectedOption = 0;
    bool selectLevel(sf::RenderWindow& window, int selectedOption);
    int getSelectedOption();
    void setSelectedOption(int option);
    void initializeLevel(LevelType levelType, Pad& pad, Ball& ball, std::vector<Brick>& bricks);
    void renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, std::vector<Brick>& bricks);

    LevelType getCurrentLevel()  { return currentLevel; } 
private:
    LevelType currentLevel;
>>>>>>> Eric
};
