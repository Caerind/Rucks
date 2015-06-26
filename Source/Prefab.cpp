#include "Prefab.hpp"

Prefab::Prefab(es::EntityManager& manager) : mManager(manager)
{
}

es::Entity::Ptr Prefab::createPlayer(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>("soldier1");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(0,0,64,64));
    e->getComponent<SpriteComponent>().setOrigin(sf::Vector2f(32.f,32.f));

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(34.f,64.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(17.f,32.f));

    // Collision
    e->addComponent<CollisionComponent>();
    e->getComponent<CollisionComponent>().setSize(sf::Vector2f(20.f,20.f));
    e->getComponent<CollisionComponent>().setOrigin(sf::Vector2f(10.f,-10.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(200.f);

    // Animation
    e->addComponent<AnimationComponent>();
    e->getComponent<AnimationComponent>().setSheetSize(sf::Vector2i(64,64));
    e->getComponent<AnimationComponent>().setWalkDuration(sf::seconds(0.8f));

    // Life
    e->addComponent<LifeComponent>(100,200);
    e->getComponent<LifeComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<LifeComponent>().setOrigin(sf::Vector2f(0.f,30.f));

    // Player
    e->addComponent<PlayerComponent>();

    // Inventory
    e->addComponent<InventoryComponent>();

    // Weapon
    //e->addComponent<WeaponComponent>(WeaponComponent::Type::Bow);

    return e;
}

es::Entity::Ptr Prefab::createMonster(sf::Vector2f const& position, MonsterComponent::Type type)
{
    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>(MonsterComponent::getTextureId(type));
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(0,0,32,32));
    e->getComponent<SpriteComponent>().setOrigin(sf::Vector2f(16.f,16.f));

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(34.f,64.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(17.f,32.f));

    // Collision
    e->addComponent<CollisionComponent>();
    e->getComponent<CollisionComponent>().setSize(sf::Vector2f(20.f,20.f));
    e->getComponent<CollisionComponent>().setOrigin(sf::Vector2f(10.f,-10.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(100.f);

    // Animation
    e->addComponent<AnimationComponent>();
    e->getComponent<AnimationComponent>().setSheetSize(sf::Vector2i(32,32));
    e->getComponent<AnimationComponent>().setWalkDuration(sf::seconds(0.8f));

    // Life
    e->addComponent<LifeComponent>(100,200);
    e->getComponent<LifeComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<LifeComponent>().setOrigin(sf::Vector2f(0.f,30.f));

    // AI
    e->addComponent<AIComponent>();
    e->getComponent<AIComponent>().setViewDistance(300.f);
    e->getComponent<AIComponent>().setOutOfView(500.f);

    // Monster
    e->addComponent<MonsterComponent>(type);

    // Inventory
    e->addComponent<InventoryComponent>();

    // Weapon
    //e->addComponent<WeaponComponent>(MonsterComponent::getRange(type),MonsterComponent::getDamage(type),MonsterComponent::getCooldown(type));
    return e;
}

es::Entity::Ptr Prefab::createPacific(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>("princess");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(0,0,64,64));
    e->getComponent<SpriteComponent>().setOrigin(sf::Vector2f(32.f,32.f));

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(34.f,64.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(17.f,32.f));

    // Collision
    e->addComponent<CollisionComponent>();
    e->getComponent<CollisionComponent>().setSize(sf::Vector2f(20.f,20.f));
    e->getComponent<CollisionComponent>().setOrigin(sf::Vector2f(10.f,-10.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(150.f);

    // Animation
    e->addComponent<AnimationComponent>();
    e->getComponent<AnimationComponent>().setSheetSize(sf::Vector2i(64,64));
    e->getComponent<AnimationComponent>().setWalkDuration(sf::seconds(0.8f));

    // Life
    e->addComponent<LifeComponent>(100,200);
    e->getComponent<LifeComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<LifeComponent>().setOrigin(sf::Vector2f(0.f,30.f));

    // AI
    e->addComponent<AIComponent>();
    e->getComponent<AIComponent>().setViewDistance(200.f);
    e->getComponent<AIComponent>().setOutOfView(400.f);

    // Inventory
    e->addComponent<InventoryComponent>();

    // Weapon
    //e->addComponent<WeaponComponent>(WeaponComponent::Type::Bow);

    return e;
}

es::Entity::Ptr Prefab::createFighter(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>("soldier2");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(0,0,64,64));
    e->getComponent<SpriteComponent>().setOrigin(sf::Vector2f(32.f,32.f));

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(34.f,64.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(17.f,32.f));

    // Collision
    e->addComponent<CollisionComponent>();
    e->getComponent<CollisionComponent>().setSize(sf::Vector2f(20.f,20.f));
    e->getComponent<CollisionComponent>().setOrigin(sf::Vector2f(10.f,-10.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(100.f);

    // Animation
    e->addComponent<AnimationComponent>();
    e->getComponent<AnimationComponent>().setSheetSize(sf::Vector2i(64,64));
    e->getComponent<AnimationComponent>().setWalkDuration(sf::seconds(0.8f));

    // Life
    e->addComponent<LifeComponent>(100,200);
    e->getComponent<LifeComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<LifeComponent>().setOrigin(sf::Vector2f(0.f,30.f));

    // AI
    e->addComponent<AIComponent>();
    e->getComponent<AIComponent>().setViewDistance(300.f);
    e->getComponent<AIComponent>().setOutOfView(500.f);

    // Inventory
    e->addComponent<InventoryComponent>();

    // Weapon
    //e->addComponent<WeaponComponent>(WeaponComponent::Type::Sword);

    return e;
}

es::Entity::Ptr Prefab::createProjectile(sf::Vector2f const& position, ProjectileComponent::Type type, sf::Vector2f const& direction)
{
    es::Entity::Ptr e = mManager.create();

    // Transform
    /*e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    e->addComponent<SpriteComponent>(ProjectileComponent::getTextureId(type));
    e->getComponent<SpriteComponent>().setTextureRect(ProjectileComponent::getTextureRect(type));
    e->addComponent<BoxComponent>();
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(250.f);

    e->addComponent<ProjectileComponent>(type);
    e->getComponent<ProjectileComponent>().setDirection(direction);
    e->getComponent<ProjectileComponent>().setRange(800);
    e->getComponent<ProjectileComponent>().setSpeed(300);
    e->getComponent<ProjectileComponent>().setDamage(10);
    */
    return e;
}

es::Entity::Ptr Prefab::createItem(sf::Vector2f const& position, Item item)
{
    es::Entity::Ptr e = mManager.create();

    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    e->addComponent<SpriteComponent>("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(16,0,16,32));

    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(16.f,32.f));

    e->addComponent<ItemComponent>();
    e->getComponent<ItemComponent>().setItem(item);

    return e;
}

