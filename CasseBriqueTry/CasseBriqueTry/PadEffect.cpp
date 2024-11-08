#include "PadEffect.h"
#include <iostream>

<<<<<<< HEAD
PadEffect::PadEffect(PadEffectType type, Pad& pad, int duration,
    std::function<void(Pad&)> applyCallback,
    std::function<void(Pad&)> removeCallback)
    : type(type), pad(pad), duration(duration), isActive(false),
    applyCallback(applyCallback), removeCallback(removeCallback) {}

void PadEffect::applyEffect() {
    if (!isActive) {
        applyCallback(pad);
        isActive = true;
    }
}

void PadEffect::removeEffect() {
    if (isActive) {
        removeCallback(pad);
        isActive = false;
    }
}

=======
>>>>>>> Eric
void PadEffect::update(float deltaTime) {
    if (isActive && duration > 0) {
        duration -= deltaTime;
        if (duration <= 0) {
<<<<<<< HEAD
            removeEffect();
=======
            isActive = false;
            removePadEffect();
>>>>>>> Eric
        }
    }
}

<<<<<<< HEAD
bool PadEffect::isEffectActive() const {
    return isActive;
}

std::string PadEffect::PadEffectTypeToString()  {
    switch (type) {
    case PadEffectType::PadSpeedBoost: return "Speed Boost";
    case PadEffectType::PadSpeedNerf: return "Speed Nerf";
    case PadEffectType::PadSizeBoost: return "Size Increase";
    case PadEffectType::PadSizeNerf: return "Size Decrease";
    /*case PadEffectType::PadShield: return "Invert Controls";*/
    default: return "Unknown Effect";
    }
}


=======
void PadEffect::display() {
    if (isActive) {
        std::cout << "Effet actif : " << PadEffectTypeToString(type) << " sur le pad en position ("
            << pad.getPosition().first << ", " << pad.getPosition().second << ") "<< std::endl;
    }
    else {
        std::cout << "Effet inactif : " << PadEffectTypeToString(type) << " sur le pad en position ("
            << pad.getPosition().first << ", " << pad.getPosition().second << ") " << std::endl;
    }
    
}

std::string PadEffect::PadEffectTypeToString(PadEffectType type) {
    switch (type) {
    case PadEffectType::PadSpeedBoost: return "Speed Boost";
    case PadEffectType::PadSpeedNerf: return "Speed Nerf";
    default: return "Unknown Effect";
    }
}
>>>>>>> Eric
