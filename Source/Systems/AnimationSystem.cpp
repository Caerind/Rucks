#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem()
{
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(MovementComponent::getId());
    mFilter.push_back(AnimationComponent::getId());
}

std::string AnimationSystem::getId()
{
    return "AnimationSystem";
}

void AnimationSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2i sheetSize = mEntities[i]->getComponent<AnimationComponent>().getSheetSize();

        assert(sheetSize.x != 0);

        if (mEntities[i]->getComponent<AnimationComponent>().getWalkTime() > mEntities[i]->getComponent<AnimationComponent>().getWalkDuration())
        {
            mEntities[i]->getComponent<AnimationComponent>().resetWalkTime();
        }

        // Calc X & Y of the Sheet on the Texture
        unsigned int col, dir;
        col = static_cast<unsigned int>(mEntities[i]->getComponent<AnimationComponent>().getWalkTime().asSeconds() * (mEntities[i]->getComponent<SpriteComponent>().getTextureSize().x / sheetSize.x));
        dir = mEntities[i]->getComponent<AnimationComponent>().getDirection();

        // Update TextureRect
        mEntities[i]->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(col * sheetSize.x, dir * sheetSize.y, sheetSize.x, sheetSize.y));

        // Update The Weapon Animation
        if (mEntities[i]->hasComponent<WeaponComponent>() && !mEntities[i]->hasComponent<MonsterComponent>())
        {
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.hasWeapon())
            {
                handleWeaponOnMoving(w,sf::Vector2i(col,dir));
                if (!w.canAttack()) // !canAttack = Special Weapon Animation
                {
                    handleWeaponOnAttack(w,dir);
                }
                // TODO (#7#): Double Sprite Animation
            }
        }
    }
}

void AnimationSystem::handleWeaponOnMoving(WeaponComponent& w, sf::Vector2i sPos)
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
}

void AnimationSystem::handleWeaponOnAttack(WeaponComponent& w, unsigned int dir)
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
