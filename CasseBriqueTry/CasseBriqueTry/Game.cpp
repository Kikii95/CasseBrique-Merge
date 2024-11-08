#include "Game.h"
#include <memory>
#include "GameOver.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "FileUtils.h"
#include <filesystem>
#include "BallEffectList.h"
#include "BackgroundShader.h"  // Inclusion correcte du shader
#include "EndMenu.h"
#include "Utils.h"
#include "PauseMenu.h"

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

using json = nlohmann::json;

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Casse-Brique", sf::Style::Fullscreen),
    hud(SCREEN_WIDTH, SCREEN_HEIGHT, window),
    gameOverScreen(window),
    pad((0.8 * SCREEN_WIDTH), (0.2 * SCREEN_HEIGHT)),
    ball(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.originalSize, ball.originalSpeed, ball.originalSize),
    levelManager(),
    isOptionsMenuActive(false),
    isMainMenuActive(true),
    isPaused(false),
    endMenu(window),
    resolutionWidth(SCREEN_WIDTH),
    resolutionHeight(SCREEN_HEIGHT),
    volume(50.0f),
    padShape(sf::Vector2f(pad.getSize().first, pad.getSize().second))
{
    if (!pad.loadTexture("50-Breakout-Tiles.png")) {
        std::cerr << "Erreur : Impossible de charger la texture du pad." << std::endl;
    }

    if (!backgroundShader.loadFromMemory(fragmentShaderCode, sf::Shader::Fragment)) {
        std::cerr << "Erreur : impossible de charger le shader d'arrière-plan depuis la mémoire" << std::endl;
    }
    else {
        std::cout << "Shader chargé avec succès depuis la mémoire" << std::endl;
    }

    if (!heartTexture.loadFromFile("heart.png")) {
        std::cerr << "Erreur : Impossible de charger la texture de coeur" << std::endl;
    }
    if (!heartLostTexture.loadFromFile("heart_black.png")) {
        std::cerr << "Erreur : Impossible de charger la texture de coeur perdu" << std::endl;
    }

    for (int i = 0; i < 3; ++i) {
        sf::Sprite heart(heartTexture);
        heart.setScale(0.000018f * SCREEN_WIDTH, 0.000018f * SCREEN_WIDTH);
        heart.setPosition(20 + i * (heart.getGlobalBounds().width + 10), 0);
        hearts.push_back(heart);
    }

    loadBrickTexture();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    padShape.setFillColor(sf::Color::Blue);
    Brick::loadTextures();
    createInitialBricks(7, 14, (SCREEN_WIDTH / 16), (SCREEN_HEIGHT / 27));
}

void Game::createInitialBricks(int rows, int columns, int brickWidth, int brickHeight) {
    int totalWidth = columns * brickWidth;
    int startX = (SCREEN_WIDTH - totalWidth) / 2;
    int topOffset = 150;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int xPos = startX + j * brickWidth;
            int yPos = topOffset + i * brickHeight;
            Brick newBrick(xPos, yPos, brickWidth, brickHeight);
            bricks.push_back(newBrick);
        }
    }
}

void Game::loadBricksFromJson() {
    std::ifstream file("level_3.json");
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible de charger le fichier JSON level_3.json" << std::endl;
        return;
    }

    json levelData;
    file >> levelData;

    for (const auto& brickData : levelData["bricks"]) {
        int posX = brickData["positionX"];
        int posY = brickData["positionY"];
        int width = brickData["sizeX"];
        int height = brickData["sizeY"];
        bricks.emplace_back(posX, posY, width, height);

        std::cout << "Brique chargée : Position (" << posX << ", " << posY
            << "), Taille (" << width << ", " << height << ")" << std::endl;
    }

    std::cout << "Toutes les briques ont été chargées depuis level_3.json" << std::endl;
}

void Game::restartGame() {
    isGameOver = false;
    isMainMenuActive = true;
    isPaused = false;
    lives = 3;
    score = 0;
    bonusCount = 0;
    bricks.clear();
    hearts.clear();
    activeBallEffects.clear();
    isBallLaunched = false;

    ball.setPosition(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize() / 2);
    ball.setSpeed(400);
    loadBrickTexture();

    hud.getMainMenu().reset();
    hud.updateScore(score);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();

        if (isLevelEditorActive) {
            window.clear();
            levelGenerator.drawGrid(window);
            window.display();
        }
        else if (!isMainMenuActive && !isPaused && !isGameOver) {
            update(deltaTime);
        }

        render();
    }
}

void Game::resetBall() {
    for (auto& effect : activeBallEffects) {
        effect->removeEffect();
    }
    activeBallEffects.clear();
    if (activeBalls.empty()) {
        Ball newBall(pad.getPosition().first + pad.getSize().first / 2,
            pad.getPosition().second - ball.originalSize / 2,
            ball.originalSpeed,
            ball.originalSize);
        activeBalls.push_back(newBall);
    }

    Ball& mainBall = activeBalls.front();
    mainBall.setPosition(pad.getPosition().first + pad.getSize().first / 2,
        pad.getPosition().second - mainBall.getSize() / 2);
    mainBall.setSpeed(ball.originalSpeed);

    float directionX;
    do {
        directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 0.8f - 0.4f;
    } while (std::abs(directionX) < 0.1f);

    mainBall.setDirection(directionX, -1.0f);
    mainBall.normalizeDirection();
    isBallLaunched = false;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (isGameOver) {
            if (gameOverScreen.handleEvent(event)) {
                isGameOver = false;
            }
        }
        else if (isMainMenuActive) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    hud.getMainMenu().moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    hud.getMainMenu().moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selectedOption = hud.getMainMenu().getSelectedItemIndex();
                    if (selectedOption == 0) {
                        isMainMenuActive = false;
                        isGameActive = true;
                    }
                    else if (selectedOption == 1) {
                        restartGame();
                        isMainMenuActive = false;
                        initializeLevelManager();
                    }
                    else if (selectedOption == 2) {
                        isMainMenuActive = false;
                        isLevelEditorActive = true;
                    }
                    else if (selectedOption == 3) {
                        window.close();
                    }
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (isGameOver) {
        return;
    }
    if (!isMainMenuActive && !isPaused && !isGameOver) {
        if (!isBallLaunched) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                float directionX;
                float directionY = -1.0f;

                do {
                    directionX = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * 0.8f - 0.4f;
                } while (std::abs(directionX) < 0.2f || std::abs(directionX) > 0.4f);

                directionY = -std::sqrt(1 - directionX * directionX);

                ball.setDirection(directionX, directionY);
                isBallLaunched = true;
            }
        }
        else {
            for (auto& ball : activeBalls) {
                ball.move(deltaTime, padShape, bricks, pad);
            }
            checkLife();
            checkVictoryCondition();
        }

        padShape.setPosition(pad.getPosition().first, pad.getPosition().second);
        for (size_t i = 0; i < bricks.size(); ++i) {
            if (!bricks[i].isBroken() && ball.getShape().getGlobalBounds().intersects(bricks[i].getShape().getGlobalBounds())) {
                bricks[i].takeHit();
                if (bricks[i].isDestroyed()) {
                    int randomEffectIndex = rand() % 22;
                    applyEffect(randomEffectIndex);
                    hud.updateScore(10);
                    bricks.erase(bricks.begin() + i);
                    i--;
                    break;
                }
                break;
            }
        }
    }
}

void Game::updateLevelEditor() {
    levelGenerator.drawGrid(window);
}

void Game::initializeMusic() {
    if (music.loadFromFile("medievale.ogg")) {
        music.setLoop(true);
        music.setVolume(volume);
        music.play();
    }
    else {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    }
}

void Game::initializeLevelManager() {
    if (!levelManager.selectLevel(window, LevelType::LEVEL_1)) {
        std::cerr << "Erreur lors de la sélection du niveau" << std::endl;
        window.close();
        return;
    }
    levelManager.initializeLevel(levelManager.getCurrentLevel(), pad, ball, bricks);
}

void Game::saveLevel() {
    int levelNumber = getNextLevelNumber();
    std::string fileName = "level_" + std::to_string(levelNumber) + ".lvl";
    std::ofstream levelFile(fileName);

    if (levelFile.is_open()) {
        for (auto& brick : bricks) {
            levelFile << brick.getPositionX() << " "
                << brick.getPositionY() << " "
                << brick.getSizeX() << " "
                << brick.getSizeY() << "\n";
        }
        levelFile.close();
        std::cout << "Niveau " << levelNumber << " enregistré sous " << fileName << std::endl;
    }
    else {
        std::cerr << "Erreur : impossible de créer le fichier " << fileName << std::endl;
    }
}

void Game::checkLife() {
    for (auto it = activeBalls.begin(); it != activeBalls.end();) {
        if (it->getPosition().second > SCREEN_HEIGHT) {
            it = activeBalls.erase(it);
        }
        else {
            ++it;
        }
    }

    if (activeBalls.empty()) {
        --lives;
        if (lives >= 0 && lives < hearts.size()) {
            hearts[lives].setTexture(heartLostTexture);
        }
        if (lives > 0) {
            resetBall();
        }
        else {
            isGameOver = true;
        }
    }
}

void Game::checkVictoryCondition() {
    bool allBroken = true;
    for (Brick& brick : bricks) {
        if (!brick.isBroken()) {
            allBroken = false;
            break;
        }
    }
    if (allBroken) {
        isVictory = true;
        isMainMenuActive = true;
        std::cout << "You win!" << std::endl;
    }
}

void Game::applyEffect(int effectIndex) {
    std::unique_ptr<BallEffect> newEffect;
    int duration = BallEffect::getEffectDuration();

    for (const auto& effect : activeBallEffects) {
        if (effect->getType() == static_cast<BallEffectType>(effectIndex)) {
            effect->resetDuration();
            return;
        }
    }

    switch (effectIndex) {
    case 0: newEffect = std::make_unique<BallSpeedBoost>(ball, activeBalls, duration); break;
    case 1: newEffect = std::make_unique<BallSpeedNerf>(ball, activeBalls, duration); break;
    case 2: newEffect = std::make_unique<BallSizeBoost>(ball, activeBalls, duration); break;
    case 3: newEffect = std::make_unique<BallSizeNerf>(ball, activeBalls, duration); break;
    case 4: newEffect = std::make_unique<BallPiercing>(ball, activeBalls, duration); break;
    case 5: newEffect = std::make_unique<BallRandomDirection>(ball, activeBalls); break;
    case 6: newEffect = std::make_unique<BallMultiplier>(ball, activeBalls, duration, 2); break;
    case 7: newEffect = std::make_unique<BallReverse>(ball, activeBalls, duration); break;
    case 8: newEffect = std::make_unique<BallTeleport>(ball, activeBalls); break;
    case 9: newEffect = std::make_unique<BallChaos>(ball, activeBalls, padShape, duration); break;
    case 10: newEffect = std::make_unique<BallInvisible>(ball, activeBalls, duration); break;
    case 11: newEffect = std::make_unique<BallSplit>(ball, activeBalls, duration); break;
    }
    activeBallEffects.push_back(std::move(newEffect));
}

void Game::loadBrickTexture() {
    // Placeholder for brick texture loading
}

int Game::getNextLevelNumber() {
    int level = 1;
    std::string filename;
    do {
        filename = "level_" + std::to_string(level) + ".json";
        std::ifstream file(filename);
        if (!file) {
            break;
        }
        level++;
    } while (true);
    return level;
}

void Game::render() {
    window.clear();
    hud.draw(window, isMainMenuActive, isPaused, isGameOver, isOptionsMenuActive);

    if (isLevelEditorActive) {
        levelGenerator.drawGrid(window);
    }
    else {
        backgroundShader.setUniform("iTime", clock.getElapsedTime().asSeconds());
        sf::Vector2f resolution(window.getSize());
        backgroundShader.setUniform("iResolution", sf::Glsl::Vec2(1920.0f, 1080.0f));
        sf::RectangleShape background(sf::Vector2f(resolution.x, resolution.y));
        background.setPosition(0, 0);
        window.draw(background, &backgroundShader);

        if (isMainMenuActive) {
            hud.draw(window, isMainMenuActive);
        }
        else if (isGameActive) {
            for (auto& heart : hearts) {
                window.draw(heart);
            }
            window.draw(ball.getShape());
            window.draw(pad.getShape());
            for (auto& ball : activeBalls) {
                window.draw(ball.getShape());
            }
            for (Brick& brick : bricks) {
                if (!brick.isBroken()) {
                    window.draw(brick.getShape());
                }
            }
        }
        else if (isGameOver) {
            endMenu.display();
        }

        window.display();
    }
}
