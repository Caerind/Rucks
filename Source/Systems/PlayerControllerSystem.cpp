#include "PlayerControllerSystem.hpp"

PlayerControllerSystem::PlayerControllerSystem()
: es::System()
, ah::ActionTarget(Configuration::instance().getPlayerInput())
{
    mFilter.requires(PlayerComponent::getId());
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(MovementComponent::getId());
    mFilter.requires(HumanComponent::getId());
    mFilter.requires(WeaponComponent::getId());
    mFilter.requires(FactionComponent::getId());
    mFilter.requires(SpellComponent::getId());
}

std::string PlayerControllerSystem::getId()
{
    return "PlayerControllerSystem";
}

void PlayerControllerSystem::update()
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::instance()));

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        // Movement
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
        }

        // Look At
        sf::Vector2f mPos = ah::Application::instance().getMousePositionView(rd::Renderer::getView());
        mEntities[i]->getComponent<HumanComponent>().setDirection(mPos);

        // To Start Projectile
        sf::Vector2f delta = mPos - mEntities[i]->getComponent<TransformComponent>().getPosition();
        sf::Vector2f dir;
        if (delta != sf::Vector2f())
        {
            dir = thor::unitVector<float>(delta);
        }

        // Weapon
        if (isActive("action"))
        {
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.canAttack())
            {
                if (w.isLongRange())
                {
                    w.attack(mPos - mEntities[i]->getComponent<TransformComponent>().getPosition());
                }
                else
                {
                    bool attacked = false;
                    auto targets = mEntities[i]->getComponent<FactionComponent>().getListOfEnemies();
                    for (std::size_t j = 0; j < targets.size(); j++)
                    {
                        if (targets[j]->getComponent<BoxComponent>().contains(mPos))
                        {
                            w.attack(targets[j]);
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

        // Spell
        if (isActive("spell1") || isActive("spell2") || isActive("spell3") || isActive("spell4") || isActive("spell5"))
        {
            std::size_t index;
            if (isActive("spell1")) index = 0;
            if (isActive("spell2")) index = 1;
            if (isActive("spell3")) index = 2;
            if (isActive("spell4")) index = 3;
            if (isActive("spell5")) index = 4;

            SpellComponent& s = mEntities[i]->getComponent<SpellComponent>();
            if (s.getSpell(index) != nullptr)
            {
                s.getSpell(index)->setStricker(mEntities[i]);
                s.getSpell(index)->setDirection(dir);
                s.getSpell(index)->setPosition(mPos);
                s.getSpell(index)->setTarget(getTarget(mPos));
                if (s.canSpell(index))
                {
                    s.spell(index);
                }
            }
        }

        rd::Renderer::getView().setCenter(mEntities[i]->getComponent<TransformComponent>().getPosition());
    }

    mMap->clearEvents();
}

es::EntityPtr PlayerControllerSystem::getTarget(sf::Vector2f const& position)
{
    es::ComponentFilter filter;
    filter.requires(StatComponent::getId());
    filter.requires(BoxComponent::getId());
    filter.requires(TransformComponent::getId());

    auto entities = World::instance().getEntities().getByFilter(filter);

    for (std::size_t i = 0; i < entities.size(); i++)
    {
        if (entities[i]->getComponent<BoxComponent>().getBounds().contains(position))
        {
            return entities[i];
        }
    }

    return nullptr;
}
