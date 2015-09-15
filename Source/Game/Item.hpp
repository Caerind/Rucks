#ifndef ITEM_HPP
#define ITEM_HPP

#include <memory>
#include <string>

class Item
{
    public:
        typedef std::shared_ptr<Item> Ptr;

        Item();

        void setId(int id);
        int getId() const;

        bool isStackable() const;

        void setName(std::string const& name);
        std::string getName() const;

        void setPrice(int price);
        int getPrice() const;

        virtual bool isWeapon() const;

    protected:
        int mId;
        std::string mName;
        int mPrice;
};

#endif // ITEM_HPP
