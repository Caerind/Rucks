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

    es::ComponentFilter filterSpellTarget;
    filterSpellTarget.requires(BoxComponent::getId());
    filterSpellTarget.requires(StatComponent::getId());
    es::EntityArray spellTarget = World::instance().getEntities().getByFilter(filterSpellTarget);

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

        es::Entity::Ptr target = nullptr;
        for (std::size_t i = 0; i < spellTarget.size(); i++)
        {
            if (spellTarget[i]->getComponent<BoxComponent>().contains(mPos))
            {
                target = spellTarget[i];
            }
        }
        sf::Vector2f dir = thor::unitVector(mPos - mEntities[i]->getComponent<TransformComponent>().getPosition());

        if (s.canSpell()) // Isnt already casting
        {
            bool spell = false;
            std::size_t id = 0;
            if (isActive("spell1"))
            {
                spell = true;
                id = 0;
            }
            if (isActive("spell2"))
            {
                spell = true;
                id = 1;
            }
            if (isActive("spell3"))
            {
                spell = true;
                id = 2;
            }
            if (isActive("spell4"))
            {
                spell = true;
                id = 3;
            }
            if (isActive("spell5"))
            {
                spell = true;
                id = 4;
            }

            Spell* selectedSpell = s.getSpell(id);
            if (spell && selectedSpell != nullptr)
            {
                selectedSpell->setStricker(mEntities[i]);
                selectedSpell->setTarget(target);
                selectedSpell->setPosition(mPos);
                selectedSpell->setDirection(dir);
                if (selectedSpell->canSpell()) // Mana Cooldown Range
                {
                    s.setActiveSpell(id);
                    s.spell();
                }
            }
        }
        else // Is casting
        {
            es::Entity::Ptr target = nullptr;
            for (std::size_t i = 0; i < spellTarget.size(); i++)
            {
                if (spellTarget[i]->getComponent<BoxComponent>().contains(mPos))
                {
                    target = spellTarget[i];
                }
            }
            sf::Vector2f dir = thor::unitVector(mPos - mEntities[i]->getComponent<TransformComponent>().getPosition());

            s.update(mEntities[i],target,mPos,dir);
        }


        World::instance().getView().setCenter(mEntities[i]->getComponent<TransformComponent>().getPosition());
        SpellHUD& spellHUD = World::instance().getHUD().getSpells();
        // TODO : update SPELL HUD
    }


    mMap->clearEvents();
}
