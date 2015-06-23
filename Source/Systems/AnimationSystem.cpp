#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem()
{
    mFilter.push_back(TransformComponent::getId());
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

        // Update Walk Time
        if (m.getLastMovement() != sf::Vector2f(0.f,0.f))
        {
            m.addWalkTime(dt);
            if (m.getWalkTime() > sf::seconds(0.8f))
            {
                m.resetWalkTime();
            }
        }
        else
        {
            m.resetWalkTime();
        }
        tRect.left = static_cast<int>(m.getWalkTime().asSeconds() * (s.getTextureSize().x / s.getSheetSize().x)) * s.getSheetSize().x;

        // Update Look At
        Direction direction;
        sf::Vector2f diff = m.getLookAt() - s.getOrigin() - mEntities[i]->getComponent<TransformComponent>().getPosition();
        float angle = static_cast<float>(atan2(diff.y,diff.x) * 180 / 3.14159265);
        if((angle > 0 && angle < 45) || (angle >= -45 && angle <= 0))
            direction = Direction::E;
        else if(angle >= 45 && angle < 135)
            direction = Direction::S;
        else if((angle >= 135 && angle <= 180) || (angle >= -180 && angle < -135))
            direction = Direction::W;
        else
            direction = Direction::N;
        tRect.top = direction * s.getSheetSize().y;

        // Update Texture Rect
        s.setTextureRect(tRect);
    }
}
