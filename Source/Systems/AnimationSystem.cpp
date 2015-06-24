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
        MovementComponent& m = mEntities[i]->getComponent<MovementComponent>();
        SpriteComponent& s = mEntities[i]->getComponent<SpriteComponent>();

        sf::IntRect tRect;
        tRect.width = s.getSheetSize().x;
        tRect.height = s.getSheetSize().y;
        tRect.left = static_cast<int>(m.getWalkTime().asSeconds() * (s.getTextureSize().x / s.getSheetSize().x)) * s.getSheetSize().x;
        tRect.top = m.getDirection() * s.getSheetSize().y;
        s.setTextureRect(tRect);
    }
}
