#include "InventoryComponent.hpp"

InventoryComponent::InventoryComponent()
{
}

std::string InventoryComponent::getId()
{
    return "InventoryComponent";
}

void InventoryComponent::addItem(Item::Ptr item)
{
    if (item != nullptr)
    {
        addItem(item->getId());
    }
}

void InventoryComponent::addItem(std::size_t itemId)
{
    if (!has(itemId) && !isFull())
    {
        mItems[itemId] = 1;
    }
    else if (has(itemId))
    {
        mItems[itemId]++;
    }
}

Item::Ptr InventoryComponent::moveLastItem()
{
    for (auto itr = mItems.begin(); itr != mItems.end(); itr++)
    {
        if (itr->second == 0)
        {
            mItems.erase(itr);
        }
    }
    for (auto itr = mItems.begin(); itr != mItems.end(); itr++)
    {
        if (itr->second > 0)
        {
            itr->second--;
            Item::Ptr item = std::make_shared<Item>();
            item->setId(itr->first);
            return item;
        }
    }
    return nullptr;
}

void InventoryComponent::setSize(std::size_t size)
{
    mSize = size;
}

std::size_t InventoryComponent::getSize() const
{
    return mSize;
}

std::size_t InventoryComponent::getItemCount() const
{
    std::size_t count = 0;
    for (auto itr = mItems.begin(); itr != mItems.end(); itr++)
    {
        count += itr->second;
    }
    return count;
}

bool InventoryComponent::isFull() const
{
    return mSize <= mItems.size();
}

bool InventoryComponent::has(std::size_t itemId) const
{
    return mItems.find(itemId) != mItems.end();
}

std::size_t InventoryComponent::amount(std::size_t itemId) const
{
    if (has(itemId))
    {
        return mItems.at(itemId);
    }
    else
    {
        return 0;
    }
}
