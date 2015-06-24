#include "World.hpp"

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

    // Attach Systems
    mEntities.addSystem<RenderSystem>(new RenderSystem());
    mEntities.addSystem<PlayerControllerSystem>(new PlayerControllerSystem());
    mEntities.addSystem<AIControllerSystem>(new AIControllerSystem());
    mEntities.addSystem<AnimationSystem>(new AnimationSystem());
    mEntities.addSystem<CollisionSystem>(new CollisionSystem(mChunks));

    Prefab prefab(mEntities);
    prefab.createPlayer(sf::Vector2f(100,100));
    prefab.createMonster(sf::Vector2f(400,400),MonsterComponent::Type::Bat);
    prefab.createMonster(sf::Vector2f(425,375),MonsterComponent::Type::Bee);
    prefab.createPacific(sf::Vector2f(50,50));
    prefab.createFighter(sf::Vector2f(50,200));
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
    mEntities.getSystem<PlayerControllerSystem>().update(dt);
    mEntities.getSystem<AIControllerSystem>().update(dt);
    mEntities.getSystem<AnimationSystem>().update(dt);

    mChunks.update(mView);
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

bool World::isOnline() const
{
    return mIsOnline;
}

bool World::isServer() const
{
    return mIsServer;
}

World::World()
{

}

World::~World()
{

}
