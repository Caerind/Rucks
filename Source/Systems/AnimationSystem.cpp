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

void AnimationSystem::update(sf::Time dt)
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
        }
    }
}
