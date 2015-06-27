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
    e->getComponent<InventoryComponent>().setSize(20);

    // Weapon
    Weapon::Ptr w = std::make_shared<Weapon>();
    w->setRange(50.f);
    w->setDamage(25);
    w->setCooldown(sf::seconds(0.2f));
    w->setType(Weapon::Type::Sword);
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setWeapon(w);
    e->getComponent<WeaponComponent>().setOrigin(16.f,64.f);

    // Spell
    e->addComponent<SpellComponent>();
    e->getComponent<SpellComponent>().setType(SpellComponent::Type::Fireball);
    e->getComponent<SpellComponent>().setRange(800.f);
    e->getComponent<SpellComponent>().setDamage(50);
    e->getComponent<SpellComponent>().setCooldown(sf::seconds(0.6f));

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
    e->getComponent<InventoryComponent>().setSize(20);

    // Weapon
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setRange(50.f);
    e->getComponent<WeaponComponent>().setDamage(5);
    e->getComponent<WeaponComponent>().setCooldown(sf::seconds(0.3f));

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
    e->getComponent<InventoryComponent>().setSize(20);

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
    e->getComponent<InventoryComponent>().setSize(20);

    // Weapon
    Weapon::Ptr w = std::make_shared<Weapon>();
    w->setRange(200.f);
    w->setDamage(30);
    w->setCooldown(sf::seconds(0.2f));
    w->setType(Weapon::Type::Bow);
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setWeapon(w);
    e->getComponent<WeaponComponent>().setOrigin(16.f,64.f);

    return e;
}

es::Entity::Ptr Prefab::createProjectile(sf::Vector2f const& position, es::Entity::Ptr stricker, sf::Vector2f const& direction)
{
    if (direction == sf::Vector2f() || stricker == nullptr)
    {
        return nullptr;
    }
    if (!stricker->hasComponent<WeaponComponent>())
    {
        return nullptr;
    }
    Weapon::Ptr weapon = stricker->getComponent<WeaponComponent>().getWeapon();
    if (weapon == nullptr)
    {
        return nullptr;
    }
    if (!weapon->isLongRange())
    {
        return nullptr;
    }

    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>();
    e->getComponent<SpriteComponent>().setTexture("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(weapon->getProjectileType() * 16, 0, 16, 32));
    e->getComponent<SpriteComponent>().setOrigin(8.f,16.f);

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(16.f,32.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(8.f,16.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(250.f);
    e->getComponent<MovementComponent>().setDirection(direction);

    // Projectile
    e->addComponent<ProjectileComponent>();
    e->getComponent<ProjectileComponent>().setStricker(stricker);
    e->getComponent<ProjectileComponent>().setType(weapon->getProjectileType());
    e->getComponent<ProjectileComponent>().setDirection(direction);
    e->getComponent<ProjectileComponent>().setRange(weapon->getRange());
    e->getComponent<ProjectileComponent>().setDamage(weapon->getDamage());

    return e;
}

es::Entity::Ptr Prefab::createFireball(sf::Vector2f const& position, es::Entity::Ptr stricker, sf::Vector2f const& direction)
{
    if (direction == sf::Vector2f() || stricker == nullptr)
    {
        return nullptr;
    }
    if (!stricker->hasComponent<SpellComponent>())
    {
        return nullptr;
    }

    sf::Vector2f unitDir = thor::unitVector<float>(direction);

    es::Entity::Ptr e = mManager.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position + 32.f * unitDir);

    // Sprite
    e->addComponent<SpriteComponent>();
    e->getComponent<SpriteComponent>().setTexture("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(ProjectileComponent::Type::Fireball * 16, 0, 16, 32));
    e->getComponent<SpriteComponent>().setOrigin(8.f,16.f);

    // Box
    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(16.f,32.f));
    e->getComponent<BoxComponent>().setOrigin(sf::Vector2f(8.f,16.f));

    // Movement
    e->addComponent<MovementComponent>();
    e->getComponent<MovementComponent>().setSpeed(250.f);
    e->getComponent<MovementComponent>().setDirection(direction);

    // Projectile
    e->addComponent<ProjectileComponent>();
    e->getComponent<ProjectileComponent>().setStricker(stricker);
    e->getComponent<ProjectileComponent>().setType(ProjectileComponent::Type::Fireball);
    e->getComponent<ProjectileComponent>().setDirection(direction);
    e->getComponent<ProjectileComponent>().setRange(stricker->getComponent<SpellComponent>().getRange());
    e->getComponent<ProjectileComponent>().setDamage(stricker->getComponent<SpellComponent>().getDamage());

    return e;
}


es::Entity::Ptr Prefab::createItem(sf::Vector2f const& position, Item::Ptr item)
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

