#include "ProjectileSystem.hpp"

ProjectileSystem::ProjectileSystem()
{
    mFilter.push_back(ProjectileComponent::getId());
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
}

std::string ProjectileSystem::getId()
{
    return "ProjectileSystem";
}

void ProjectileSystem::update(sf::Time dt)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        // TODO (#3#): Projectile Update
        ProjectileComponent& p = mEntities[i]->getComponent<ProjectileComponent>();
        sf::Vector2f mvt;
        mvt = p.getSpeed() * dt.asSeconds() * p.getDirection();
        // TODO (#3#): Projectile Collision
        mEntities[i]->getComponent<TransformComponent>().move(mvt);
        p.addDistanceTraveled(mvt);
        if (p.fallDown())
        {
            // TODO (#5#): Handle fall down
        }
    }
}
