#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"

#include "../Components.hpp"

#include <SFML/System/Time.hpp>

class MovementSystem : public es::System
{
    public:
        MovementSystem();

        static std::string getId();

        void update(sf::Time dt);
};

#endif // MOVEMENTSYSTEM_HPP
