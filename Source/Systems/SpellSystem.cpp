#include "SpellSystem.hpp"

SpellSystem::SpellSystem()
{
    mFilter.requires(SpellComponent::getId());
}

std::string SpellSystem::getId()
{
    return "SpellSystem";
}

void SpellSystem::update(sf::Time dt)
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        mEntities[i]->getComponent<SpellComponent>().update(dt);
    }
}
