#include "FactionComponent.hpp"
#include "../World.hpp"

FactionComponent::FactionComponent()
{
    mFactionId = 0;
}

std::string FactionComponent::getId()
{
    return "FactionComponent";
}

void FactionComponent::setFactionId(int factionId)
{
    mFactionId = factionId;
}

int FactionComponent::getFactionId() const
{
    return mFactionId;
}

Faction FactionComponent::getFaction()
{
    return World::instance().getFactions().get(mFactionId);
}

es::EntityArray FactionComponent::getListOfEnemies()
{
    bool isPlayer = false;
    if (hasParent())
    {
        isPlayer = mParent->hasComponent<PlayerComponent>();
    }

    es::ComponentFilter filter;
    filter.requires(StatComponent::getId());
    filter.requires(FactionComponent::getId());
    filter.requires(BoxComponent::getId());
    filter.requires(TransformComponent::getId());

    auto entities = World::instance().getEntities().getByFilter(filter);

    for (std::size_t i = 0; i < entities.size(); i++)
    {
        if (!isPlayer)
        {
            if (!getFaction().isEnemy(entities[i]->getComponent<FactionComponent>().getFactionId()))
            {
                entities.erase(entities.begin() + i);
            }
        }
        else
        {
            if (getFaction().isAlly(entities[i]->getComponent<FactionComponent>().getFactionId()))
            {
                entities.erase(entities.begin() + i);
            }
        }
    }

    return entities;
}
