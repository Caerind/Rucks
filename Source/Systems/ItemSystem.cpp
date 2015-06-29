#include "ItemSystem.hpp"
#include "../World.hpp"

ItemSystem::ItemSystem()
{
    mFilter.requires(InventoryComponent::getId());
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
                itemFilter.requires(TransformComponent::getId());
                itemFilter.requires(SpriteComponent::getId());
                itemFilter.requires(BoxComponent::getId());
                itemFilter.requires(ItemComponent::getId());

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
        if (mEntities[i]->hasComponent<StatComponent>() && !mEntities[i]->hasComponent<PlayerComponent>() && mEntities[i]->hasComponent<TransformComponent>())
        {
            if (mEntities[i]->getComponent<StatComponent>().isDead())
            {
                while (mEntities[i]->getComponent<InventoryComponent>().getItemCount() > 0)
                {
                    Item::Ptr item = mEntities[i]->getComponent<InventoryComponent>().moveLastItem();
                    if (item != nullptr)
                    {
                        sf::Vector2f position = mEntities[i]->getComponent<TransformComponent>().getPosition();
                        position.x += thor::random(-20.f,20.f);
                        position.y += thor::random(-20.f,20.f);
                        World::instance().getPrefab().createItem(position,item);
                    }
                }
            }
        }
    }
}
