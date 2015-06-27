#include "ItemComponent.hpp"

ItemComponent::ItemComponent()
{
    mItem = nullptr;
    mHasItem = false;
}

std::string ItemComponent::getId()
{
    return "ItemComponent";
}

void ItemComponent::setItem(Item::Ptr item)
{
    mItem = item;
    if (mItem != nullptr)
    {
        mHasItem = true;
    }
    else
    {
        mHasItem = false;
    }
}

Item::Ptr ItemComponent::getItem() const
{
    if (mHasItem)
    {
        return mItem;
    }
    return nullptr;
}

Item::Ptr ItemComponent::moveItem()
{
    Item::Ptr i = nullptr;
    if (hasItem())
    {
        i = std::make_shared<Item>(*getItem());
    }
    removeItem();
    return i;
}

void ItemComponent::removeItem()
{
    mItem = nullptr;
    mHasItem = false;
}

bool ItemComponent::hasItem() const
{
    return mHasItem;
}
