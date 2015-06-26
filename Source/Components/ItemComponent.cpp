#include "ItemComponent.hpp"

ItemComponent::ItemComponent()
{
    mHasItem = false;
}

std::string ItemComponent::getId()
{
    return "ItemComponent";
}

void ItemComponent::setItem(Item item)
{
    mItem = item;
    mHasItem = true;
}

Item ItemComponent::getItem() const
{
    return mItem;
}

Item ItemComponent::moveItem()
{
    Item i;
    if (mHasItem)
    {
        i = mItem;
    }
    mItem = Item();
    mHasItem = false;
    return i;
}

void ItemComponent::removeItem()
{
    mItem = Item();
    mHasItem = false;
}

bool ItemComponent::hasItem() const
{
    return mHasItem;
}
