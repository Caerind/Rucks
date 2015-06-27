#include "ProjectileSystem.hpp"
#include "../World.hpp"

ProjectileSystem::ProjectileSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(MovementComponent::getId());
    mFilter.push_back(BoxComponent::getId());
    mFilter.push_back(ProjectileComponent::getId());
}

std::string ProjectileSystem::getId()
{
    return "ProjectileSystem";
}

void ProjectileSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        bool remove = false;

        ProjectileComponent& p = mEntities[i]->getComponent<ProjectileComponent>();

        // Collision
        if (p.getDistanceTraveled() > 100.f)
        {
            es::Entity::Ptr e = nullptr;
            sf::FloatRect r = mEntities[i]->getComponent<BoxComponent>().getBounds();
            if (World::instance().getEntities().getSystem<CollisionSystem>().projectileCollision(r,e))
            {
                if (e != nullptr) // If we have touched an entity with life component
                {

                    if (e->hasComponent<LifeComponent>())
                    {
                        e->getComponent<LifeComponent>().inflige(p.getDamage());
                    }
                }
                else // If we have touched a collide tile
                {
                }
                remove = true;
            }
        }

        // Arrow on the ground
        if (p.fallDown() && p.getType() == ProjectileComponent::Type::Arrow)
        {
            World::instance().getPrefab().createItem(mEntities[i]->getComponent<TransformComponent>().getPosition(),std::make_shared<Item>());
            remove = true;
        }

        // Remove it
        if (remove)
        {
            mManager->remove(mEntities[i]);
        }
    }
}
