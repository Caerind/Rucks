#ifndef AICONTROLLERSYSTEM_HPP
#define AICONTROLLERSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/Components.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIControllerSystem : public es::System
{
    public:
        AIControllerSystem();

        static std::string getId();

        void update(sf::Time dt);

        void handleMonster(es::Entity::Ptr e, sf::Time dt);
        void handleFighter(es::Entity::Ptr e, sf::Time dt);
        void handlePacific(es::Entity::Ptr e, sf::Time dt);

        void handleAttack(es::Entity::Ptr e);
};

#endif // AICONTROLLERSYSTEM_HPP
