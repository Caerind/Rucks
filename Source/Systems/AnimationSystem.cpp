#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem()
{
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(MovementComponent::getId());
}

std::string AnimationSystem::getId()
{
    return "AnimationSystem";
}

void AnimationSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2i sheetSize = mEntities[i]->getComponent<SpriteComponent>().getSheetSize();

        // Calc X & Y of the Sheet on the Texture
        unsigned int col = static_cast<unsigned int>(mEntities[i]->getComponent<MovementComponent>().getWalkTime().asSeconds() * (mEntities[i]->getComponent<SpriteComponent>().getTextureSize().x / sheetSize.x));
        unsigned int dir = mEntities[i]->getComponent<MovementComponent>().getDirection();

        // Update TextureRect
        mEntities[i]->getComponent<SpriteComponent>().setTextureRect(sf::IntRect(col * sheetSize.x, dir * sheetSize.y, sheetSize.x, sheetSize.y));

        // Update The Weapon Animation
        if (mEntities[i]->hasComponent<WeaponComponent>() && !mEntities[i]->hasComponent<MonsterComponent>())
        {
            // TODO (#3#): Weapon Animation
            WeaponComponent& w = mEntities[i]->getComponent<WeaponComponent>();
            if (w.canAttack()) // canAttack = No Special Weapon Animation
            {
                handleWeaponOnMoving(w,sf::Vector2i(col,dir));
            }
            else // !canAttack = Special Weapon Animation
            {
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
