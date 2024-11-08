#pragma once
<<<<<<< HEAD
#include <functional>
#include <string>
#include <vector>
#include "Pad.h"
=======
#include "pad.h"

>>>>>>> Eric

enum class PadEffectType {
    PadSpeedBoost,
    PadSpeedNerf,
<<<<<<< HEAD
    PadSizeBoost,
    PadSizeNerf,
    PadSticky,
    PadInvertedControls,
    PadMagnet,
    PadProjectile,
    PadShield,
    PadBallMultiplier,
    PadSliding,
    PadSplit,
    PadEnergyDrain,
=======
>>>>>>> Eric
};

class PadEffect {
protected:
    PadEffectType type;
<<<<<<< HEAD
    Pad& pad;
    int duration;
    bool isActive;
    std::function<void(Pad&)> applyCallback;
    std::function<void(Pad&)> removeCallback;


public:
    PadEffect(PadEffectType type, Pad& pad, int duration,
        std::function<void(Pad&)> applyCallback,
        std::function<void(Pad&)> removeCallback);

    virtual ~PadEffect() = default;

    virtual void applyEffect();
    virtual void removeEffect();
    virtual void update(float deltaTime);
    bool isEffectActive() const;
    std::string PadEffectTypeToString() ;
    virtual PadEffectType getType()  = 0;

=======
    Pad& pad; 
    int duration;
    bool isActive;

public:
    PadEffect(PadEffectType type, Pad& pad, int duration)
        : type(type), pad(pad), duration(duration), isActive(false) {}

    virtual ~PadEffect() = default;
    std::string PadEffectTypeToString(PadEffectType type);
    virtual void applyPadEffect() = 0;
    virtual void removePadEffect() = 0;
    void update(float deltaTime);  
    void display();  

    bool isEffectActive()  { return isActive; }
>>>>>>> Eric
};
