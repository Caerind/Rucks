#include "ProjectileSystem.hpp"
#include "../World.hpp"

ProjectileSystem::ProjectileSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(ProjectileComponent::getId());
}

std::string ProjectileSystem::getId()
{
    return "ProjectileSystem";
}

void ProjectileSystem::update(sf::Time dt)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        bool remove = false;

        ProjectileComponent& p = mEntities[i]->getComponent<ProjectileComponent>();
        sf::Vector2f mvt;
        mvt = p.getSpeed() * dt.asSeconds() * p.getDirection();
        mEntities[i]->getComponent<TransformComponent>().move(mvt);

        // Collision
        if (p.getDistanceTraveled() > 100.f)
        {
            es::Entity::Ptr e = nullptr;
            sf::FloatRect r = mEntities[i]->getComponent<BoxComponent>().getBounds();
            if (World::instance().getEntities().getSystem<CollisionSystem>().projectileCollision(r,e))
            {
                if (e != nullptr) // If we have touched an entity with life component
                {
                    e->getComponent<LifeComponent>().inflige(p.getDamage());
                }
                remove = true;
            }
        }

        // Add Distance
        p.addDistanceTraveled(mvt);
        if (p.fallDown() && p.getType() == ProjectileComponent::Type::Arrow)
        {
            World::instance().getPrefab().createItem(mEntities[i]->getComponent<TransformComponent>().getPosition(),Item());
            remove = true;
        }

        // Remove it
        if (remove)
        {
            mManager->remove(mEntities[i]);
        }
    }
}
