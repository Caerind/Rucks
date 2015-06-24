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

        void findTarget(es::Entity::Ptr e);
        void handleGoToTarget(es::Entity::Ptr e, sf::Time dt);
        void handleAttack(es::Entity::Ptr e);
        void handleEscapeTarget(es::Entity::Ptr e, sf::Time dt);
        void handleNoTarget(es::Entity::Ptr e, sf::Time dt);
};

#endif // AICONTROLLERSYSTEM_HPP
