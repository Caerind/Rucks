#ifndef AICONTROLLERSYSTEM_HPP
#define AICONTROLLERSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/TransformComponent.hpp"
#include "../Components/MovementComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/AIComponent.hpp"
#include "../Components/LifeComponent.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIControllerSystem : public es::System
{
    public:
        AIControllerSystem();

        static std::string getId();

        void update(sf::Time dt);

        void handleMonster(es::Entity::Ptr e, sf::Time dt);
};

#endif // AICONTROLLERSYSTEM_HPP
