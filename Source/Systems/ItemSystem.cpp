#include "ItemSystem.hpp"

ItemSystem::ItemSystem()
{
    mFilter.push_back(InventoryComponent::getId());
}

std::string ItemSystem::getId()
{
    return "ItemSystem";
}

void ItemSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        // If an entity want to pick up an item on the ground
        if (mEntities[i]->hasComponent<BoxComponent>())
        {
            sf::FloatRect r = mEntities[i]->getComponent<BoxComponent>().getBounds();

            if (hasManager() && !mEntities[i]->getComponent<InventoryComponent>().isFull())
            {
                es::ComponentFilter itemFilter;
                itemFilter.push_back(TransformComponent::getId());
                itemFilter.push_back(SpriteComponent::getId());
                itemFilter.push_back(BoxComponent::getId());
                itemFilter.push_back(ItemComponent::getId());

                es::EntityArray items = mManager->getByFilter(itemFilter);

                for (unsigned int j = 0; j < items.size(); j++)
                {
                    if (items[j]->getComponent<BoxComponent>().intersects(r) && items[j]->getComponent<ItemComponent>().hasItem())
                    {
                        mEntities[i]->getComponent<InventoryComponent>().addItem(items[j]->getComponent<ItemComponent>().moveItem());
                        mManager->remove(items[j]);
                    }
                }
            }
        }

        // If an entity which isn't the player died : this entity drop his inventory
        if (mEntities[i]->hasComponent<LifeComponent>() && !mEntities[i]->hasComponent<PlayerComponent>())
        {
            // TODO : Drop Inventory
        }
    }
}
