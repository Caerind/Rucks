#ifndef PLAYERCONTROLLERSYSTEM_HPP
#define PLAYERCONTROLLERSYSTEM_HPP

#include <SFML/System/Time.hpp>

#include "../../Lib/EntitySystem/System.hpp"
#include "../../Lib/Aharos/ActionTarget.hpp"

#include "../Components/Components.hpp"

class PlayerControllerSystem : public es::System, public ah::ActionTarget
{
    public:
        PlayerControllerSystem();

        static std::string getId();

        void update(sf::Time dt);

    private:
        sf::Vector2f mMovement;
};

#endif // PLAYERCONTROLLERSYSTEM_HPP
