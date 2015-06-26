#ifndef PROJECTILESYSTEM_HPP
#define PROJECTILESYSTEM_HPP

#include "../Components.hpp"
#include "../../Lib/EntitySystem/System.hpp"
#include <SFML/System/Time.hpp>

class ProjectileSystem : public es::System
{
    public:
        ProjectileSystem();

        static std::string getId();

        void update(sf::Time dt);
};

#endif // PROJECTILESYSTEM_HPP
