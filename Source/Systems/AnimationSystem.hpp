#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/Components.hpp"

#include <SFML/System/Time.hpp>

class AnimationSystem : public es::System
{
    public:
        AnimationSystem();

        static std::string getId();

        void update();

        void handleWeaponOnMoving(WeaponComponent& w, sf::Vector2i sPos);
        void handleWeaponOnAttack(WeaponComponent& w, unsigned int dir);
};

#endif // ANIMATIONSYSTEM_HPP
