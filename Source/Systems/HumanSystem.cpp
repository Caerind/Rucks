#include "HumanSystem.hpp"

HumanSystem::HumanSystem()
{
    mFilter.requires(HumanComponent::getId());
    mFilter.requires(MovementComponent::getId());
}

std::string HumanSystem::getId()
{
    return "HumanSystem";
}

void HumanSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2i sheetSize = mEntities[i]->getComponent<HumanComponent>().getSheetSize();

        assert(sheetSize.x != 0);

        if (mEntities[i]->getComponent<HumanComponent>().getWalkTime() > mEntities[i]->getComponent<HumanComponent>().getWalkDuration())
        {
            mEntities[i]->getComponent<HumanComponent>().resetWalkTime();
        }

        // Calc X & Y of the Sheet on the Texture
        sf::Vector2i tCoords;
        tCoords.x = mEntities[i]->getComponent<HumanComponent>().getWalkTime().asSeconds() * (mEntities[i]->getComponent<HumanComponent>().getTextureSize().x / sheetSize.x);
        tCoords.y = mEntities[i]->getComponent<HumanComponent>().getDirection();

        // Update TextureRect
        mEntities[i]->getComponent<HumanComponent>().setTextureRect(sf::IntRect(tCoords.x * sheetSize.x, tCoords.y * sheetSize.y, sheetSize.x, sheetSize.y));

        // Update The Weapon Animation
        if (mEntities[i]->hasComponent<WeaponComponent>())
        {
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.hasWeapon())
            {
                handleWeaponOnMoving(w,tCoords);
                if (!w.canAttack())
                {
                    handleWeaponOnAttack(w,tCoords.y);
                    // TODO : Double Sprite Animation
                }
            }
        }

        // Update The Spell Animation
        if (mEntities[i]->hasComponent<SpellComponent>())
        {
            SpellComponent& s = mEntities[i]->getComponent<SpellComponent>();
            if (s.isCasting())
            {
                mEntities[i]->getComponent<HumanComponent>().setLeftArmTexture("male_spellcast_larm");
                handleSpell(s,tCoords.y,mEntities[i]);
            }
            else
            {
                mEntities[i]->getComponent<HumanComponent>().setLeftArmTexture("male_walkcycle_larm");
            }
        }
    }
}

void HumanSystem::handleWeaponOnMoving(WeaponComponent& w, sf::Vector2i sPos)
{
    // Direction : N
    if (sPos == sf::Vector2i(0,0)) w.setWeaponTransform(11,14,10);
    if (sPos == sf::Vector2i(1,0)) w.setWeaponTransform(11,14,9);
    if (sPos == sf::Vector2i(2,0)) w.setWeaponTransform(11,14,5);
    if (sPos == sf::Vector2i(3,0)) w.setWeaponTransform(11,12,3);
    if (sPos == sf::Vector2i(4,0)) w.setWeaponTransform(11,12,0);
    if (sPos == sf::Vector2i(5,0)) w.setWeaponTransform(11,15,3);
    if (sPos == sf::Vector2i(6,0)) w.setWeaponTransform(11,17,5);
    if (sPos == sf::Vector2i(7,0)) w.setWeaponTransform(11,17,9);
    if (sPos == sf::Vector2i(8,0)) w.setWeaponTransform(11,16,10);
    if (sPos.y == 0) { w.setZ(8.f); }

    // Direction : W
    if (sPos == sf::Vector2i(0,1)) w.setWeaponTransform(-6,14,-80);
    if (sPos == sf::Vector2i(1,1)) w.setWeaponTransform(-1,12,-77);
    if (sPos == sf::Vector2i(2,1)) w.setWeaponTransform(-1,12,-75);
    if (sPos == sf::Vector2i(3,1)) w.setWeaponTransform(-2,12,-77);
    if (sPos == sf::Vector2i(4,1)) w.setWeaponTransform(-8,14,-80);
    if (sPos == sf::Vector2i(5,1)) w.setWeaponTransform(-9,14,-77);
    if (sPos == sf::Vector2i(6,1)) w.setWeaponTransform(-8,14,-75);
    if (sPos == sf::Vector2i(7,1)) w.setWeaponTransform(-3,11,-77);
    if (sPos == sf::Vector2i(8,1)) w.setWeaponTransform(-3,12,-80);
    if (sPos.y == 1) { w.setZ(8.f); }

    // Direction : S
    if (sPos == sf::Vector2i(0,2)) w.setWeaponTransform(-10,15,-10);
    if (sPos == sf::Vector2i(1,2)) w.setWeaponTransform(-10,15,-9);
    if (sPos == sf::Vector2i(2,2)) w.setWeaponTransform(-10,17,-5);
    if (sPos == sf::Vector2i(3,2)) w.setWeaponTransform(-10,19,-3);
    if (sPos == sf::Vector2i(4,2)) w.setWeaponTransform(-10,17,-0);
    if (sPos == sf::Vector2i(5,2)) w.setWeaponTransform(-10,16,-3);
    if (sPos == sf::Vector2i(6,2)) w.setWeaponTransform(-10,14,-5);
    if (sPos == sf::Vector2i(7,2)) w.setWeaponTransform(-10,14,-9);
    if (sPos == sf::Vector2i(8,2)) w.setWeaponTransform(-10,14,-10);
    if (sPos.y == 2) { w.setZ(24.f); }

    // Direction : E
    if (sPos == sf::Vector2i(0,3)) w.setWeaponTransform(-7,16,80);
    if (sPos == sf::Vector2i(1,3)) w.setWeaponTransform(-1,16,77);
    if (sPos == sf::Vector2i(2,3)) w.setWeaponTransform(-3,16,75);
    if (sPos == sf::Vector2i(3,3)) w.setWeaponTransform(-9,16,77);
    if (sPos == sf::Vector2i(4,3)) w.setWeaponTransform(-10,17,80);
    if (sPos == sf::Vector2i(5,3)) w.setWeaponTransform(-12,17,77);
    if (sPos == sf::Vector2i(6,3)) w.setWeaponTransform(-10,18,75);
    if (sPos == sf::Vector2i(7,3)) w.setWeaponTransform(-7,17,77);
    if (sPos == sf::Vector2i(8,3)) w.setWeaponTransform(-4,16,80);
    if (sPos.y == 3) { w.setZ(24.f); }
}

void HumanSystem::handleWeaponOnAttack(WeaponComponent& w, int dir)
{
    sf::Time attack = w.getTimeSinceLastAttack();
    sf::Time touch = w.getCooldown() * 0.25f;
    sf::Time end = w.getCooldown() - touch;
    if (attack < touch)
    {
        float d = attack.asSeconds() / touch.asSeconds();
        switch (dir)
        {
            // f(d) = d * (end - begin) + begin;
            case 0: w.setRotation(d * (-20 - 6) + 6); break;
            case 1: w.setRotation(d * (-50 + 77.5) - 77.5); break;
            case 2: w.setRotation(d * (20 + 6) - 6); break;
            case 3: w.setRotation(d * (50 - 77.5) + 77.5); break;
        }
    }
    else
    {
        float d = (attack.asSeconds()-touch.asSeconds()) / end.asSeconds();
        switch (dir)
        {
            // f(d) = d * (end - begin) + begin;
            case 0: w.setRotation(d * (6 + 20) - 20); break;
            case 1: w.setRotation(d * (-77.5 + 50) - 50); break;
            case 2: w.setRotation(d * (-6 - 20) + 20); break;
            case 3: w.setRotation(d * (77.5 - 50) + 50); break;
        }
    }
}

void HumanSystem::handleSpell(SpellComponent& s, int dir, es::Entity::Ptr e)
{
    float percent = 0.f;
    int p = 0;
    if (s.getActiveSpell() != nullptr)
    {
        if (s.getActiveSpell()->getCast() != sf::Time::Zero)
        {
            percent = s.getCasting().asSeconds() / s.getActiveSpell()->getCast().asSeconds();
            p = (int)(percent * 7.f);
            percent *= 100.f;
        }
    }

    float x = 0, y = 0;
    // TODO : Spell

    // Direction : N
    if (dir == 0 && p == 0) s.setSpellPosition(20,49);
    if (dir == 0 && p == 1) s.setSpellPosition(22,46);
    if (dir == 0 && p == 2) s.setSpellPosition(23,42);
    if (dir == 0 && p == 3) s.setSpellPosition(16,40);
    if (dir == 0 && p == 4) s.setSpellPosition(10,32);
    if (dir == 0 && p == 5) s.setSpellPosition(11,30);
    if (dir == 0 && p == 6) s.setSpellPosition(16,40);
    if (dir == 0) { s.setZ(24.f); }

    // Direction : W
    if (dir == 1 && p == 0) s.setSpellPosition(x,y);
    if (dir == 1 && p == 1) s.setSpellPosition(x,y);
    if (dir == 1 && p == 2) s.setSpellPosition(x,y);
    if (dir == 1 && p == 3) s.setSpellPosition(x,y);
    if (dir == 1 && p == 4) s.setSpellPosition(x,y);
    if (dir == 1 && p == 5) s.setSpellPosition(x,y);
    if (dir == 1 && p == 6) s.setSpellPosition(x,y);
    if (dir == 1) { s.setZ(24.f); }

    // Direction : S
    if (dir == 2 && p == 0) s.setSpellPosition(x,y);
    if (dir == 2 && p == 1) s.setSpellPosition(x,y);
    if (dir == 2 && p == 2) s.setSpellPosition(x,y);
    if (dir == 2 && p == 3) s.setSpellPosition(x,y);
    if (dir == 2 && p == 4) s.setSpellPosition(x,y);
    if (dir == 2 && p == 5) s.setSpellPosition(x,y);
    if (dir == 2 && p == 6) s.setSpellPosition(x,y);
    if (dir == 2) { s.setZ(8.f); }

    // Direction : E
    if (dir == 3 && p == 0) s.setSpellPosition(x,y);
    if (dir == 3 && p == 1) s.setSpellPosition(x,y);
    if (dir == 3 && p == 2) s.setSpellPosition(x,y);
    if (dir == 3 && p == 3) s.setSpellPosition(x,y);
    if (dir == 3 && p == 4) s.setSpellPosition(x,y);
    if (dir == 3 && p == 5) s.setSpellPosition(x,y);
    if (dir == 3 && p == 6) s.setSpellPosition(x,y);
    if (dir == 3) { s.setZ(8.f); }

    // Left Arm Texture
    if (p == 7) p = 0;
    sf::Vector2i sheetSize = e->getComponent<HumanComponent>().getSheetSize();
    e->getComponent<HumanComponent>().setLeftArmTextureRect(sf::IntRect(p * sheetSize.x, dir * sheetSize.y, sheetSize.x, sheetSize.y));
}
