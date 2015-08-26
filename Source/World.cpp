#include "World.hpp"
#include "../Lib/Aharos/Application.hpp"

World World::mInstance;

World& World::instance()
{
    return mInstance;
}

void World::initialize()
{
    mIsOnline = false;
    mIsServer = false;

    // Load resources
    mResources.loadTexture("tileset","Assets/Textures/tileset.png");
    mResources.loadTexture("soldier1","Assets/Textures/soldier1.png");
    mResources.getTexture("soldier1").setSmooth(true);
    mResources.loadTexture("soldier2","Assets/Textures/soldier2.png");
    mResources.getTexture("soldier2").setSmooth(true);
    mResources.loadTexture("princess","Assets/Textures/princess.png");
    mResources.getTexture("princess").setSmooth(true);
    MonsterComponent::loadMonsterTextures();
    WeaponComponent::loadWeaponTextures();
    ProjectileComponent::loadProjectileTextures();

    // Attach Systems
    mEntities.addSystem<RenderSystem>();
    mEntities.addSystem<PlayerControllerSystem>();
    mEntities.addSystem<MovementSystem>();
    mEntities.addSystem<AnimationSystem>();
    mEntities.addSystem<CollisionSystem>();
    mEntities.getSystem<CollisionSystem>().setChunks(mChunks);
    mEntities.addSystem<LifeSystem>();
    mEntities.addSystem<ItemSystem>();
    mEntities.addSystem<AIControllerSystem>();
    mEntities.addSystem<ProjectileSystem>();

    mEntities.getSystem<RenderSystem>().renderDebug(true);

    // Load Entities
    mPrefab.createPlayer(sf::Vector2f(0,0));
    mPrefab.createItem(sf::Vector2f(200,200), std::make_shared<Item>());
    mPrefab.createMonster(sf::Vector2f(400,300),MonsterComponent::Type::Bat);
    mPrefab.createMonster(sf::Vector2f(425,375),MonsterComponent::Type::Bee);
    mPrefab.createPacific(sf::Vector2f(50,50));
    mPrefab.createFighter(sf::Vector2f(50,200));
}

void World::terminate()
{
    mChunks.clear();
    mEntities.removeAll();

    // Release resources
    mResources.releaseTexture("tileset");
    mResources.releaseTexture("soldier1");
    mResources.releaseTexture("soldier2");
    mResources.releaseTexture("princess");
    MonsterComponent::releaseMonsterTextures();
    WeaponComponent::releaseWeaponTextures();
    ProjectileComponent::releaseProjectileTextures();
}

bool World::loadFromFile(std::string const& filename)
{
    return true;
}

bool World::saveToFile(std::string const& filename)
{
    return true;
}

void World::handleEvent(sf::Event const& event)
{
    mEntities.getSystem<PlayerControllerSystem>().handleEvent(event);

    // Zoom
    if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta < 1)
        {
            if (mView.getSize().x < 1024.f)
                mView.zoom(1.2f);
        }
        else
        {
            if (mView.getSize().x > 320.f)
                mView.zoom(0.8f);
        }
    }
}

void World::update(sf::Time dt)
{
    mEntities.update();

    mEntities.getSystem<PlayerControllerSystem>().update();
    mEntities.getSystem<AIControllerSystem>().update();
    mEntities.getSystem<MovementSystem>().update(dt); // Controller Before Movement
    mEntities.getSystem<AnimationSystem>().update();

    mEntities.getSystem<ProjectileSystem>().update();

    mEntities.getSystem<ItemSystem>().update(); // Just before the life system to allow drop inventory
    mEntities.getSystem<LifeSystem>().update(); // Update in last

    mChunks.update(mView);

    ah::Application::instance().setDebugInfo("entities",ah::to_string(mEntities.getEntitiesCount()));
}

void World::render(sf::RenderTarget& target)
{
    sf::View defaultView = target.getView();
    target.setView(mView);
    mChunks.draw(target, mView, 0);
    mChunks.draw(target, mView, 1);
    mEntities.getSystem<RenderSystem>().render(target);
    mChunks.draw(target, mView, 2);
    target.setView(defaultView);
    target.draw(mHUD);
}

ah::ResourceHolder& World::getResources()
{
    return mResources;
}

sf::View& World::getView()
{
    return mView;
}

ChunkManager& World::getChunks()
{
    return mChunks;
}

es::EntityManager& World::getEntities()
{
    return mEntities;
}

Prefab& World::getPrefab()
{
    return mPrefab;
}

HUD& World::getHUD()
{
    return mHUD;
}

bool World::isOnline() const
{
    return mIsOnline;
}

bool World::isServer() const
{
    return mIsServer;
}

World::World() : mPrefab(mEntities)
{

}

World::~World()
{

}
