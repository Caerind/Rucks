#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
    public:
        Item();

        void setName(std::string const& name);
        std::string getName() const;

        void setPrice(int price);
        int getPrice() const;

    protected:
        std::string mName;
        int mPrice;
};

#endif // ITEM_HPP
