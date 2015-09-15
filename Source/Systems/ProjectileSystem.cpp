#include "ProjectileSystem.hpp"
#include "../World.hpp"
#include "../../Aharos/Application/Application.hpp"

ProjectileSystem::ProjectileSystem()
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(SpriteComponent::getId());
    mFilter.requires(MovementComponent::getId());
    mFilter.requires(BoxComponent::getId());
    mFilter.requires(ProjectileComponent::getId());
}

std::string ProjectileSystem::getId()
{
    return "ProjectileSystem";
}

void ProjectileSystem::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        bool remove = false;

        ProjectileComponent& p = mEntities[i]->getComponent<ProjectileComponent>();

        // Collision
        es::Entity::Ptr e = nullptr;
        sf::FloatRect r = mEntities[i]->getComponent<BoxComponent>().getBounds();
        if (World::instance().getEntities().getSystem<CollisionSystem>().projectileCollision(r,e))
        {
            auto s = p.getStricker();
            if (e != nullptr && s != nullptr) // If we have touched an entity with life component
            {
                if (e->hasComponent<StatComponent>() && e != s)
                {
                    if (e->getComponent<StatComponent>().inflige(p.getDamage()) && s->hasComponent<StatComponent>()) // TODO : Better Formule For Damage
                    {
                        s->getComponent<StatComponent>().addExperience(10); // TODO : Add Experience
                    }
                    remove = true;
                }
            }
            else if (s != nullptr)
            {
                remove = true;
            }
        }

        // Test if fall down
        if (p.fallDown())
        {
            if (p.getType() == ProjectileComponent::Type::Arrow)
            {
                World::instance().createItem(mEntities[i]->getComponent<TransformComponent>().getPosition(),std::make_shared<Item>());
            }
            remove = true;
        }

        // Remove it
        if (remove)
        {
            mManager->remove(mEntities[i]);
        }
    }
}
