#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "../Lib/EntitySystem/EntitySystem.hpp"

#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/LifeComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/AIComponent.hpp"

class Prefab
{
    public:
        Prefab(es::EntityManager& manager);

        es::Entity::Ptr createPlayer(sf::Vector2f const& position);
        es::Entity::Ptr createMonster(sf::Vector2f const& position);
        es::Entity::Ptr createPacific(sf::Vector2f const& position);
        es::Entity::Ptr createFighter(sf::Vector2f const& position);

    private:
        es::EntityManager& mManager;
};

#endif // PREFAB_HPP
