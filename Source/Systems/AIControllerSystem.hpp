#ifndef AICONTROLLERSYSTEM_HPP
#define AICONTROLLERSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIControllerSystem : public es::System
{
    public:
        AIControllerSystem();

        static std::string getId();

        void update();

        void findTarget(es::Entity::Ptr e);
        void handleGoToTarget(es::Entity::Ptr e);
        void handleAttack(es::Entity::Ptr e);
        void handleEscapeTarget(es::Entity::Ptr e);
        void handleNoTarget(es::Entity::Ptr e);
};

#endif // AICONTROLLERSYSTEM_HPP
