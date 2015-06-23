#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include <SFML/System/Time.hpp>

#include "../../Lib/EntitySystem/System.hpp"
#include "../../Lib/Aharos/ActionTarget.hpp"

#include "../Components/TransformComponent.hpp"
#include "../Components/MovementComponent.hpp"
#include "../Components/PlayerInputComponent.hpp"

class PlayerInputSystem : public es::System, public ah::ActionTarget
{
    public:
        PlayerInputSystem();

        static std::string getId();

        void update(sf::Time dt);

    private:
        sf::Vector2f mMovement;
};

#endif // PLAYERINPUTSYSTEM_HPP
