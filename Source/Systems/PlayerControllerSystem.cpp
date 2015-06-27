#include "PlayerControllerSystem.hpp"
#include "../Configuration.hpp"
#include "../World.hpp"
#include "../../Lib/Aharos/Application.hpp"

PlayerControllerSystem::PlayerControllerSystem()
: es::System()
, ah::ActionTarget(Configuration::instance().getPlayerInput())
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(MovementComponent::getId());
    mFilter.requires(PlayerComponent::getId());
}

std::string PlayerControllerSystem::getId()
{
    return "PlayerControllerSystem";
}

void PlayerControllerSystem::update()
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::instance()));

    sf::Vector2f mPos = ah::Application::instance().getMousePositionView(World::instance().getView());

    es::ComponentFilter filterMonster;
    filterMonster.requires(MonsterComponent::getId());
    es::EntityArray monster = World::instance().getEntities().getByFilter(filterMonster);

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2f direction;
        if (isActive("up"))
        {
            direction.y -= 1.f;
        }
        if (isActive("left"))
        {
            direction.x -= 1.f;
        }
        if (isActive("down"))
        {
            direction.y += 1.f;
        }
        if (isActive("right"))
        {
            direction.x += 1.f;
        }
        // TODO : Speed Down The Player If He Dont Goes In The Direction He Looks At
        mEntities[i]->getComponent<MovementComponent>().setDirection(direction);
        mEntities[i]->getComponent<AnimationComponent>().setDirection(mPos);

        if (isActive("action"))
        {
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.canAttack())
            {
                w.attack(mPos - mEntities[i]->getComponent<TransformComponent>().getPosition());
                if (!w.isLongRange())
                {
                    // Attack Monster
                    for (unsigned int j = 0; j < monster.size(); j++)
                    {
                        if (thor::length(mEntities[i]->getComponent<TransformComponent>().getPosition() - monster[j]->getComponent<TransformComponent>().getPosition()) < w.getRange()
                        && monster[j]->getComponent<BoxComponent>().getBounds().contains(mPos))
                        {
                            monster[j]->getComponent<LifeComponent>().inflige(w.getDamage());
                        }
                    }
                }
            }
        }

        World::instance().getView().setCenter(mEntities[i]->getComponent<TransformComponent>().getPosition());
    }


    mMap->clearEvents();
}
