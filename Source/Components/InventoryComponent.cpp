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
    mItems.push_back(item);
}

Item::Ptr InventoryComponent::moveLastItem()
{
    if (mItems.size() > 0)
    {
        Item::Ptr i = nullptr;
        if (mItems.back() != nullptr)
        {
            i = std::make_shared<Item>(*mItems.back());
        }
        mItems.back() = nullptr;
        mItems.pop_back();
        return i;
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
    return mItems.size();
}

bool InventoryComponent::isFull() const
{
    return mSize <= mItems.size();
}
