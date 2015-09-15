#include "World.hpp"
#include "../Aharos/Application/Application.hpp"

World World::mInstance;

World& World::instance()
{
    return mInstance;
}

void World::initialize()
{
    rd::Renderer::getView().setSize(static_cast<sf::Vector2f>(ah::Application::instance().getSize()));

    mMap.load();

    mResources.loadTexture("male_walkcycle_body","Assets/Textures/male_walkcycle_body.png");
    mResources.loadTexture("male_walkcycle_legs","Assets/Textures/male_walkcycle_legs.png");
    mResources.loadTexture("male_walkcycle_rarm","Assets/Textures/male_walkcycle_rarm.png");
    mResources.loadTexture("male_walkcycle_larm","Assets/Textures/male_walkcycle_larm.png");
    mResources.loadTexture("male_spellcast_larm","Assets/Textures/male_spellcast_larm.png");
    mResources.loadTexture("weapons","Assets/Textures/weapons.png");
    mResources.loadTexture("projectiles","Assets/Textures/projectiles.png");
    mResources.loadTexture("spell","Assets/Textures/spell.png");

    mResources.getTexture("male_walkcycle_body").setSmooth(true);
    mResources.getTexture("male_walkcycle_legs").setSmooth(true);
    mResources.getTexture("male_walkcycle_rarm").setSmooth(true);
    mResources.getTexture("male_walkcycle_larm").setSmooth(true);
    mResources.getTexture("male_spellcast_larm").setSmooth(true);
    mResources.getTexture("weapons").setSmooth(true);
    mResources.getTexture("projectiles").setSmooth(true);
    mResources.getTexture("spell").setSmooth(true);

    mEntities.addSystem<PlayerControllerSystem>();
    mEntities.addSystem<MovementSystem>();
    mEntities.addSystem<LifeSystem>();
    mEntities.addSystem<HumanSystem>();
    mEntities.addSystem<CollisionSystem>(mMap);
    mEntities.addSystem<SpellSystem>();
    mEntities.addSystem<ProjectileSystem>();
    mEntities.addSystem<ItemSystem>();
    mEntities.addSystem<AIControllerSystem>();

    mFactions.create(1);
    mFactions.get(1).setName("LostEmpire");
    mFactions.get(1).addEnemy(2);

    mFactions.create(2);
    mFactions.get(2).setName("The Evil");
    mFactions.get(2).addEnemy(1);

    /*
    // Load Entities
    createPlayer(sf::Vector2f(0,0));
    createItem(sf::Vector2f(200,200), std::make_shared<Item>());
    createMonster(sf::Vector2f(400,300),MonsterComponent::Type::Bat);
    createMonster(sf::Vector2f(425,375),MonsterComponent::Type::Bee);
    createPacific(sf::Vector2f(50,50));
    createFighter(sf::Vector2f(50,200));
    */

    createPlayer(sf::Vector2f(100,100));
}

void World::terminate()
{

    mMap.save();
}

void World::handleEvent(sf::Event const& event)
{
    // Zoom
    sf::View& view = rd::Renderer::getView();
    if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta < 1)
        {
            if (view.getSize().x < 1024.f)
                view.zoom(1.2f);
        }
        else
        {
            if (view.getSize().x > 320.f)
                view.zoom(0.8f);
        }
    }

    // Get a BOW
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
    {
        Weapon::Ptr w = std::make_shared<Weapon>();
        w->setType(Weapon::Type::Bow);
        w->setDamage(20,25);
        mEntities.get(1)->getComponent<WeaponComponent>().setWeapon(w);
    }

    // Get a SWORD
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X)
    {
        Weapon::Ptr w = std::make_shared<Weapon>();
        w->setType(Weapon::Type::Sword);
        w->setDamage(20,25);
        mEntities.get(1)->getComponent<WeaponComponent>().setWeapon(w);
    }

    // Spawn an Enemy
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
    {
        createAlly(ah::Application::instance().getMousePositionView(rd::Renderer::getView()));
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
    {
        createEnemy(ah::Application::instance().getMousePositionView(rd::Renderer::getView()));
    }

    mEntities.getSystem<PlayerControllerSystem>().handleEvent(event);
}

void World::update(sf::Time dt)
{
    // Update debug infos
    sf::Vector2f m = ah::Application::instance().getMousePositionView(rd::Renderer::getView());
    sf::Vector2i gC = sf::Vector2i(map::Orthogonal::worldToGlobalCoords(m));
    sf::Vector2f p = map::Orthogonal::globalCoordsToWorld(gC);
    ah::Application::instance().setDebugInfo("mouse",lp::to_string(m.x) + " " + lp::to_string(m.y));
    ah::Application::instance().setDebugInfo("chunk",lp::to_string(map::Orthogonal::worldToChunk(m).x) + " " + lp::to_string(map::Orthogonal::worldToChunk(m).y));
    ah::Application::instance().setDebugInfo("global",lp::to_string(gC.x) + " " + lp::to_string(gC.y));
    ah::Application::instance().setDebugInfo("local",lp::to_string(map::Orthogonal::worldToLocalCoords(m).x) + " " + lp::to_string(map::Orthogonal::worldToLocalCoords(m).y));
    ah::Application::instance().setDebugInfo("entities",lp::to_string(mEntities.getEntitiesCount()));
    ah::Application::instance().setDebugInfo("tile-id",lp::to_string(mMap.getTileId(gC,0)));
    ah::Application::instance().setDebugInfo("tile-collide",lp::to_string(mMap.isCollide(gC,0)));

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Update the map
        mMap.update(rd::Renderer::getView());

        // Update Entities
        mEntities.update();

        mEntities.getSystem<PlayerControllerSystem>().update();
        mEntities.getSystem<AIControllerSystem>().update();
        mEntities.getSystem<ProjectileSystem>().update(); // Controller for projectile

        mEntities.getSystem<SpellSystem>().update(dt);


        mEntities.getSystem<MovementSystem>().update(dt);
        mEntities.getSystem<HumanSystem>().update();


        mEntities.getSystem<ItemSystem>().update(); // Just before the life system to allow drop inventory
        mEntities.getSystem<LifeSystem>().update(); // Update in last
    }
}

void World::render(sf::RenderTarget& target)
{
    rd::Renderer::render(target);

    /*
    sf::View defaultView = target.getView();
    target.setView(mView);
    mChunks.draw(target, mView, 0);
    mChunks.draw(target, mView, 1);
    mEntities.getSystem<RenderSystem>().render(target);
    mChunks.draw(target, mView, 2);
    target.setView(defaultView);
    target.draw(mHUD);
    */
}

ah::ResourceHolder& World::getResources()
{
    return mResources;
}

es::EntityManager& World::getEntities()
{
    return mEntities;
}

FactionManager& World::getFactions()
{
    return mFactions;
}

World::World()
: Prefab()
, mResources()
, mMap()
{
}

World::~World()
{
}
