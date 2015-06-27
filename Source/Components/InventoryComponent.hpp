#ifndef INVENTORYCOMPONENT_HPP
#define INVENTORYCOMPONENT_HPP

#include <vector>
#include "../../Lib/EntitySystem/Component.hpp"
#include "../Game/Item.hpp"

class InventoryComponent : public es::Component
{
    public:
        InventoryComponent();

        static std::string getId();

        void addItem(Item::Ptr item);

        void setSize(std::size_t size);
        std::size_t getSize() const;

        std::size_t getItemCount() const;
        bool isFull() const;

    private:
        std::size_t mSize;
        std::vector<Item::Ptr> mItems;
};

#endif // INVENTORYCOMPONENT_HPP
