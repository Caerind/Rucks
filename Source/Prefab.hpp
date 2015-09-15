#ifndef PREFAB_HPP
#define PREFAB_HPP

#include "../Aharos/EntitySystem/EntitySystem.hpp"

#include <SFML/System/Vector2.hpp>
#include <memory>

class Spell;
class Item;

class Prefab
{
    public:
        Prefab();

        es::Entity::Ptr createPlayer(sf::Vector2f const& position);
        es::Entity::Ptr createEnemy(sf::Vector2f const& position);
        es::Entity::Ptr createAlly(sf::Vector2f const& position);
        es::Entity::Ptr createProjectile(sf::Vector2f const& position, sf::Vector2f const& direction, std::size_t strickerId = 0);
        es::Entity::Ptr createSpellBall(sf::Vector2f const& position, sf::Vector2f const& direction, Spell* spell, std::size_t strickerId = 0);
        es::Entity::Ptr createItem(sf::Vector2f const& position, std::shared_ptr<Item> item);

    protected:
        es::EntityManager mEntities;
};

#endif // PREFAB_HPP
