#include "Prefab.hpp"

Prefab::Prefab(es::EntityManager& manager) : mManager(manager)
{
}

es::Entity::Ptr Prefab::createPlayer(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position,sf::Vector2f(40,64)));
    e->addComponent<SpriteComponent>(new SpriteComponent("soldier1",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::FloatRect(0,20,16,16)));
    e->addComponent<MovementComponent>(new MovementComponent(200));
    e->addComponent<LifeComponent>(new LifeComponent(200,200));
    e->addComponent<PlayerComponent>(new PlayerComponent());
    e->addComponent<WeaponComponent>(new WeaponComponent(50,10,sf::seconds(0.3)));
    return e;
}

es::Entity::Ptr Prefab::createMonster(sf::Vector2f const& position, MonsterComponent::Type type)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position,MonsterComponent::getSize(type)));
    e->addComponent<SpriteComponent>(new SpriteComponent(MonsterComponent::getTextureId(type),MonsterComponent::getSheetSize(type)));
    e->addComponent<CollisionComponent>(new CollisionComponent(MonsterComponent::getCollisionBox(type)));
    e->addComponent<MovementComponent>(new MovementComponent(MonsterComponent::getSpeed(type)));
    e->addComponent<LifeComponent>(new LifeComponent(MonsterComponent::getLife(type),MonsterComponent::getLife(type)));
    e->addComponent<AIComponent>(new AIComponent(MonsterComponent::getViewDistance(type),MonsterComponent::getOutOfView(type)));
    e->addComponent<MonsterComponent>(new MonsterComponent(type));
    e->addComponent<WeaponComponent>(new WeaponComponent(50,10,sf::seconds(0.3)));
    return e;
}

es::Entity::Ptr Prefab::createPacific(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position,sf::Vector2f(40,64)));
    e->addComponent<SpriteComponent>(new SpriteComponent("princess",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::FloatRect(0,20,16,16)));
    e->addComponent<MovementComponent>(new MovementComponent(150));
    e->addComponent<LifeComponent>(new LifeComponent(50,50));
    e->addComponent<AIComponent>(new AIComponent(200,500,AIComponent::Type::Pacific));
    return e;
}

es::Entity::Ptr Prefab::createFighter(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position,sf::Vector2f(40,64)));
    e->addComponent<SpriteComponent>(new SpriteComponent("soldier2",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::FloatRect(0,20,16,16)));
    e->addComponent<MovementComponent>(new MovementComponent(100));
    e->addComponent<LifeComponent>(new LifeComponent(100,100));
    e->addComponent<AIComponent>(new AIComponent(300,500));
    e->addComponent<WeaponComponent>(new WeaponComponent(50,10,sf::seconds(0.3)));
    return e;
}

