#include "Prefab.hpp"

#include "Components.hpp"
#include "Spells.hpp"

#include "../Game/Item.hpp"
#include "../Game/Weapon.hpp"

Prefab::Prefab()
{
}

es::Entity::Ptr Prefab::createPlayer(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mEntities.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Player
    e->addComponent<PlayerComponent>();

    // Faction
    e->addComponent<FactionComponent>();
    e->getComponent<FactionComponent>().setFactionId(1);

    // Stat
    e->addComponent<StatComponent>();
    e->getComponent<StatComponent>().setLife(100);
    e->getComponent<StatComponent>().setLifeMax(200);
    e->getComponent<StatComponent>().setMana(1000);
    e->getComponent<StatComponent>().setManaMax(1000);
    e->getComponent<StatComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<StatComponent>().setPosition(sf::Vector2f(0.f,-30.f));

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

    // Human
    e->addComponent<HumanComponent>();
    e->getComponent<HumanComponent>().setPosition(position);

    // Weapon
    Weapon::Ptr w = std::make_shared<Weapon>();
    w->setType(Weapon::Type::Bow);
    w->setDamage(20,25);
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setWeapon(w);

    // Spell
    e->addComponent<SpellComponent>();
    e->getComponent<SpellComponent>().setSpell(0,new Fireball());
    e->getComponent<SpellComponent>().setSpell(1,new Flash());
    e->getComponent<SpellComponent>().setSpell(2,new Heal());
    e->getComponent<SpellComponent>().setSpell(3,new Lightning());

    // Inventory
    e->addComponent<InventoryComponent>();
    e->getComponent<InventoryComponent>().setSize(20);

    return e;
}

es::Entity::Ptr Prefab::createEnemy(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mEntities.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // AI
    e->addComponent<AIComponent>();
    e->getComponent<AIComponent>().setViewDistance(300.f);
    e->getComponent<AIComponent>().setOutOfView(500.f);

    // Faction
    e->addComponent<FactionComponent>();
    e->getComponent<FactionComponent>().setFactionId(2);

    // Stat
    e->addComponent<StatComponent>();
    e->getComponent<StatComponent>().setLife(100);
    e->getComponent<StatComponent>().setLifeMax(200);
    e->getComponent<StatComponent>().setMana(1000);
    e->getComponent<StatComponent>().setManaMax(1000);
    e->getComponent<StatComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<StatComponent>().setPosition(sf::Vector2f(0.f,-30.f));

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
    e->getComponent<MovementComponent>().setSpeed(180.f);

    // Human
    e->addComponent<HumanComponent>();
    e->getComponent<HumanComponent>().setPosition(position);

    // Weapon
    Weapon::Ptr w = std::make_shared<Weapon>();
    w->setType(Weapon::Type::Sword);
    w->setDamage(5,7);
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setWeapon(w);

    // Inventory
    e->addComponent<InventoryComponent>();
    e->getComponent<InventoryComponent>().setSize(20);

    return e;
}

es::Entity::Ptr Prefab::createAlly(sf::Vector2f const& position)
{
    es::Entity::Ptr e = mEntities.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // AI
    e->addComponent<AIComponent>();
    e->getComponent<AIComponent>().setViewDistance(300.f);
    e->getComponent<AIComponent>().setOutOfView(500.f);

    // Faction
    e->addComponent<FactionComponent>();
    e->getComponent<FactionComponent>().setFactionId(1);

    // Stat
    e->addComponent<StatComponent>();
    e->getComponent<StatComponent>().setLife(100);
    e->getComponent<StatComponent>().setLifeMax(200);
    e->getComponent<StatComponent>().setMana(1000);
    e->getComponent<StatComponent>().setManaMax(1000);
    e->getComponent<StatComponent>().setLifeBarSize(sf::Vector2f(30.f,6.f));
    e->getComponent<StatComponent>().setPosition(sf::Vector2f(0.f,-30.f));

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
    e->getComponent<MovementComponent>().setSpeed(180.f);

    // Human
    e->addComponent<HumanComponent>();
    e->getComponent<HumanComponent>().setPosition(position);

    // Weapon
    Weapon::Ptr w = std::make_shared<Weapon>();
    w->setType(Weapon::Type::Sword);
    w->setDamage(5,7);
    e->addComponent<WeaponComponent>();
    e->getComponent<WeaponComponent>().setWeapon(w);

    // Inventory
    e->addComponent<InventoryComponent>();
    e->getComponent<InventoryComponent>().setSize(20);

    return e;
}

es::Entity::Ptr Prefab::createProjectile(sf::Vector2f const& position, sf::Vector2f const& direction, std::size_t strickerId)
{
    if (direction == sf::Vector2f())
    {
        return nullptr;
    }
    es::Entity::Ptr stricker = World::instance().getEntities().get(strickerId);
    if (stricker == nullptr)
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

    es::Entity::Ptr e = mEntities.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>();
    e->getComponent<SpriteComponent>().setTexture("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(1 * 16, 0, 16, 32));
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
    e->getComponent<ProjectileComponent>().setStrickerId(strickerId);
    e->getComponent<ProjectileComponent>().setType(ProjectileComponent::Type::Arrow);
    e->getComponent<ProjectileComponent>().setDirection(direction);
    e->getComponent<ProjectileComponent>().setRange(weapon->getRange());
    e->getComponent<ProjectileComponent>().setDamage(weapon->getDamage());

    return e;
}

es::Entity::Ptr Prefab::createSpellBall(sf::Vector2f const& position, sf::Vector2f const& direction, Spell* spell, std::size_t strickerId)
{
    if (direction == sf::Vector2f() || spell == nullptr)
    {
        return nullptr;
    }

    es::Entity::Ptr e = mEntities.create();

    // Transform
    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // Sprite
    e->addComponent<SpriteComponent>();
    e->getComponent<SpriteComponent>().setTexture("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(2 * 16, 0, 16, 32)); // TODO : Update Texture
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
    e->getComponent<ProjectileComponent>().setStrickerId(strickerId);
    e->getComponent<ProjectileComponent>().setType(ProjectileComponent::Type::Fireball); // TODO : Other Spell Ball
    e->getComponent<ProjectileComponent>().setDirection(direction);
    e->getComponent<ProjectileComponent>().setRange(spell->getRange());
    e->getComponent<ProjectileComponent>().setDamage(spell->getDamage());

    return e;
}

es::Entity::Ptr Prefab::createItem(sf::Vector2f const& position, Item::Ptr item)
{
    es::Entity::Ptr e = mEntities.create();

    e->addComponent<TransformComponent>();
    e->getComponent<TransformComponent>().setPosition(position);

    // TODO : Per item texture
    e->addComponent<SpriteComponent>("projectiles");
    e->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(16,0,16,32));
    e->getComponent<SpriteComponent>().setOrigin(8.f,16.f);

    e->addComponent<BoxComponent>();
    e->getComponent<BoxComponent>().setSize(sf::Vector2f(16.f,32.f));
    e->getComponent<BoxComponent>().setOrigin(8.f,16.f);

    e->addComponent<ItemComponent>();
    e->getComponent<ItemComponent>().setItem(item);

    return e;
}

