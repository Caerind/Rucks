#ifndef INVENTORYCOMPONENT_HPP
#define INVENTORYCOMPONENT_HPP

#include <vector>
#include "../../Aharos/EntitySystem/Component.hpp"
#include "../Game/Item.hpp"

class InventoryComponent : public es::Component
{
    public:
        InventoryComponent();

        static std::string getId();

        void addItem(Item::Ptr item);
        void addItem(std::size_t itemId);

        Item::Ptr moveLastItem();

        void setSize(std::size_t size);
        std::size_t getSize() const;

        std::size_t getItemCount() const;
        bool isFull() const;

        bool has(std::size_t itemId) const;
        std::size_t amount(std::size_t itemId) const;

    private:
        std::size_t mSize;
        std::map<std::size_t,std::size_t> mItems; // <ItemId,Amount>
};

#endif // INVENTORYCOMPONENT_HPP
