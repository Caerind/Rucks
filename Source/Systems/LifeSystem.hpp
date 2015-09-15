#ifndef LIFESYSTEM_HPP
#define LIFESYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"
#include "../Components.hpp"

#include <SFML/System/Clock.hpp>

class LifeSystem : public es::System
{
    public:
        LifeSystem();

        static std::string getId();

        void update();

    private:
        sf::Clock mRegenerationClock;
};

#endif // LIFESYSTEM_HPP
