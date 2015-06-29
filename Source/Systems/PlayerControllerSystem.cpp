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
    mFilter.requires(WeaponComponent::getId());
    mFilter.requires(SpellComponent::getId());
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
    filterMonster.requires(BoxComponent::getId());
    filterMonster.requires(StatComponent::getId());
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
        mEntities[i]->getComponent<MovementComponent>().setDirection(direction);
        mEntities[i]->getComponent<AnimationComponent>().setDirection(mPos);

        if (isActive("action"))
        {
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            sf::Vector2f diff = mPos - mEntities[i]->getComponent<TransformComponent>().getPosition();
            if (w.canAttack())
            {
                if (w.isLongRange())
                {
                    w.attack(diff);
                }
                else
                {
                    bool attacked = false;
                    for (unsigned int j = 0; j < monster.size(); j++)
                    {
                        if (monster[j]->getComponent<BoxComponent>().contains(mPos))
                        {
                            w.attack(monster[j]);
                            attacked = true;
                        }
                    }
                    if (!attacked)
                    {
                        w.attack();
                    }
                }
            }
        }

        SpellComponent& s = mEntities[i]->getComponent<SpellComponent>();
        if (s.canSpell())
        {
            std::size_t id;
            if (isActive("spell1"))
            {
                id = 0;
            }
            if (isActive("spell2"))
            {
                id = 1;
            }
            if (isActive("spell3"))
            {
                id = 2;
            }
            if (isActive("spell4"))
            {
                id = 3;
            }
            if (isActive("spell5"))
            {
                id = 4;
            }

            if (s.getSpell(id) != nullptr)
            {
                if (s.getSpell(id)->canSpell())
                {
                    s.setActiveSpell(id);
                    s.spell();
                }
            }
        }

        World::instance().getView().setCenter(mEntities[i]->getComponent<TransformComponent>().getPosition());
    }


    mMap->clearEvents();
}
