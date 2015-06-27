#include "Item.hpp"

Item::Item()
{
}

void Item::setName(std::string const& name)
{
    mName = name;
}

std::string Item::getName() const
{
    return mName;
}

void Item::setPrice(int price)
{
    mPrice = price;
}

int Item::getPrice() const
{
    return mPrice;
}

bool Item::isWeapon() const
{
    return false;
}
