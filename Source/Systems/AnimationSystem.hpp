#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/MovementComponent.hpp"

#include <SFML/System/Time.hpp>

class AnimationSystem : public es::System
{
    public:
        AnimationSystem();

        static std::string getId();

        void update(sf::Time dt);

        enum Direction
        {
            N,
            W,
            S,
            E,
        };
};

#endif // ANIMATIONSYSTEM_HPP
