#include "PlayerControllerSystem.hpp"
#include "../Configuration.hpp"
#include "../World.hpp"
#include "../../Lib/Aharos/Application.hpp"

PlayerControllerSystem::PlayerControllerSystem()
: es::System()
, ah::ActionTarget(Configuration::instance().getPlayerInput())
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(CollisionComponent::getId());
    mFilter.push_back(MovementComponent::getId());
    mFilter.push_back(PlayerComponent::getId());
    mFilter.push_back(WeaponComponent::getId());

    bind("up",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.y == 1.f || mMovement.y == 0.f)
            mMovement.y -= 1.f;
    });
    bind("left",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.x == 1.f || mMovement.x == 0.f)
            mMovement.x -= 1.f;
    });
    bind("down",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.y == -1.f || mMovement.y == 0.f)
            mMovement.y += 1.f;
    });
    bind("right",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.x == -1.f || mMovement.x == 0.f)
            mMovement.x += 1.f;
    });
}

std::string PlayerControllerSystem::getId()
{
    return "PlayerControllerSystem";
}

void PlayerControllerSystem::update(sf::Time dt)
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::instance()));

    sf::Vector2f mPos = ah::Application::instance().getMousePositionView(World::instance().getView());

    es::ComponentFilter filterMonster;
    filterMonster.push_back(MonsterComponent::getId());
    es::EntityManager::EntityArray monster = World::instance().getEntities().getByFilter(filterMonster);

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getComponent<LifeComponent>().isDead())
        {
            mEntities[i]->getComponent<LifeComponent>().setLife(mEntities[i]->getComponent<LifeComponent>().getLifeMax());
            mEntities[i]->getComponent<TransformComponent>().setPosition(0.f,0.f);
        }

        sf::Vector2f ePos = mEntities[i]->getComponent<TransformComponent>().getPosition();
        sf::Vector2f mvt = mMovement * dt.asSeconds() * mEntities[i]->getComponent<MovementComponent>().getSpeed();
        World::instance().getEntities().getSystem<CollisionSystem>().handle(mEntities[i],mvt);

        // Update Animation
        mEntities[i]->getComponent<MovementComponent>().update(dt,mvt,ePos,mPos);

        if (isActive("action"))
        {
            // Attack Monster
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.canAttack())
            {
                w.attack();
                for (unsigned int j = 0; j < monster.size(); j++)
                {
                    if (thor::length(ePos - monster[j]->getComponent<TransformComponent>().getPosition()) < w.getRange()
                    && monster[j]->getComponent<TransformComponent>().getBoundingBox().contains(mPos))
                    {
                        monster[j]->getComponent<LifeComponent>().inflige(w.getDamage());
                    }
                }
            }
        }
    }

    if (mEntities.size() == 1)
    {
        World::instance().getView().setCenter(mEntities[0]->getComponent<TransformComponent>().getPosition());
    }

    mMovement = sf::Vector2f(0.f,0.f);

    mMap->clearEvents();
}
