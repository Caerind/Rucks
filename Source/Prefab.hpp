#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "../Lib/EntitySystem/EntitySystem.hpp"

#include "Components.hpp"

#include "../Game/Item.hpp"
#include "../Game/Weapon.hpp"

class Prefab
{
    public:
        Prefab(es::EntityManager& manager);

        es::Entity::Ptr createPlayer(sf::Vector2f const& position);
        es::Entity::Ptr createMonster(sf::Vector2f const& position, MonsterComponent::Type type);
        es::Entity::Ptr createPacific(sf::Vector2f const& position);
        es::Entity::Ptr createFighter(sf::Vector2f const& position);
        es::Entity::Ptr createProjectile(sf::Vector2f const& position, es::Entity::Ptr stricker, sf::Vector2f const& direction);
        es::Entity::Ptr createItem(sf::Vector2f const& position, Item::Ptr item);

    private:
        es::EntityManager& mManager;
};

#endif // PREFAB_HPP
