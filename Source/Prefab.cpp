#include "Prefab.hpp"

Prefab::Prefab(es::EntityManager& manager) : mManager(manager)
{
}

es::Entity::Ptr Prefab::createPlayer(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position));
    e->addComponent<SpriteComponent>(new SpriteComponent("soldier1",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::Vector2f(10,10)));
    e->addComponent<MovementComponent>(new MovementComponent(200));
    e->addComponent<LifeComponent>(new LifeComponent(200,200));
    e->addComponent<PlayerInputComponent>(new PlayerInputComponent());
    return e;
}

es::Entity::Ptr Prefab::createMonster(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position));
    e->addComponent<SpriteComponent>(new SpriteComponent("bat",sf::Vector2i(32,32)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::Vector2f(10,10)));
    e->addComponent<MovementComponent>(new MovementComponent(100));
    e->addComponent<LifeComponent>(new LifeComponent(100,100));
    e->addComponent<AIComponent>(new AIComponent());
    e->getComponent<AIComponent>().setMonster(true);
    e->getComponent<AIComponent>().setFighter(true);
    e->getComponent<AIComponent>().setViewDistance(300);
    e->getComponent<AIComponent>().setOutOfView(500);
    return e;
}

es::Entity::Ptr Prefab::createPacific(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position));
    e->addComponent<SpriteComponent>(new SpriteComponent("princess",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::Vector2f(10,10)));
    e->addComponent<MovementComponent>(new MovementComponent(150));
    e->addComponent<LifeComponent>(new LifeComponent(50,50));
    e->addComponent<AIComponent>(new AIComponent());
    e->getComponent<AIComponent>().setMonster(false);
    e->getComponent<AIComponent>().setFighter(false);
    e->getComponent<AIComponent>().setViewDistance(200);
    e->getComponent<AIComponent>().setOutOfView(500);
    return e;
}

es::Entity::Ptr Prefab::createFighter(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();
    e->addComponent<TransformComponent>(new TransformComponent(position));
    e->addComponent<SpriteComponent>(new SpriteComponent("soldier2",sf::Vector2i(64,64)));
    e->addComponent<CollisionComponent>(new CollisionComponent(sf::Vector2f(10,10)));
    e->addComponent<MovementComponent>(new MovementComponent(100));
    e->addComponent<LifeComponent>(new LifeComponent(100,100));
    e->addComponent<AIComponent>(new AIComponent());
    e->getComponent<AIComponent>().setMonster(false);
    e->getComponent<AIComponent>().setFighter(true);
    e->getComponent<AIComponent>().setViewDistance(300);
    e->getComponent<AIComponent>().setOutOfView(500);
    return e;
}

