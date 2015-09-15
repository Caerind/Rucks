#ifndef ITEMCOMPONENT_HPP
#define ITEMCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../Game/Item.hpp"

class ItemComponent : public es::Component
{
    public:
        ItemComponent();

        static std::string getId();

        void setItem(Item::Ptr item);
        Item::Ptr getItem() const;
        Item::Ptr moveItem(); // get + remove
        void removeItem();
        bool hasItem() const;

    private:
        Item::Ptr mItem;
        bool mHasItem;
};

#endif // ITEMCOMPONENT_HPP
