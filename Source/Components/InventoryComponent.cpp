#include "InventoryComponent.hpp"

InventoryComponent::InventoryComponent()
{
}

std::string InventoryComponent::getId()
{
    return "InventoryComponent";
}

void InventoryComponent::addItem(Item item)
{
    mItems.push_back(item);
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
    return mItems.size();
}

bool InventoryComponent::isFull() const
{
    return mSize == mItems.size();
}
