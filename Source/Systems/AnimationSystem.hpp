#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/Components.hpp"

class AnimationSystem : public es::System
{
    public:
        AnimationSystem();

        static std::string getId();

        void update();

        void handleWeaponOnMoving(WeaponComponent& w, sf::Vector2i sPos);
};

#endif // ANIMATIONSYSTEM_HPP
