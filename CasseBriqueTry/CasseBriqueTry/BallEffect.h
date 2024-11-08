#pragma once
#include "Ball.h"
<<<<<<< HEAD
#include <functional>
#include <string>
=======

>>>>>>> Eric

enum class BallEffectType {
    BallSpeedBoost,
    BallSpeedNerf,
<<<<<<< HEAD
    BallSizeBoost,
    BallSizeNerf,
    BallPiercing,
    BallSplit,
    BallExplosive,
    BallRandomDirection,
    BallReverse,
    BallMultiplier,
    BallTeleport,
    BallInvisible,
    BallPathPredictor,
    BallChaos,
=======
>>>>>>> Eric
};

class BallEffect {
protected:
    BallEffectType type;
<<<<<<< HEAD
    Ball& ball;
    int duration;
    bool isActive;
    std::function<void(Ball&)> applyCallback;
    std::function<void(Ball&)> removeCallback;

    static int EffectDuration;

public:
    BallEffect(BallEffectType type, Ball& ball, int duration,
        std::function<void(Ball&)> applyCallback,
        std::function<void(Ball&)> removeCallback);

    virtual ~BallEffect() = default;

    virtual void applyEffect();
    virtual void removeEffect();
    virtual void update(float deltaTime);
    void resetDuration();
    bool isEffectActive() const;
    std::string BallEffectTypeToString() const;
    
    static int getEffectDuration();

    virtual BallEffectType getType() const = 0;

    };


=======
    Ball& ball; 
    int duration;
    bool isActive;

public:
    BallEffect(BallEffectType type, Ball& ball, int duration)
        : type(type), ball(ball), duration(duration), isActive(false) {}

    virtual ~BallEffect() = default;
    std::string BallEffectTypeToString(BallEffectType type);
    virtual void applyBallEffect() = 0;
    virtual void removeBallEffect() = 0;
    void update(float deltaTime);
    void display();

    bool isEffectActive()  { return isActive; }
};
>>>>>>> Eric
