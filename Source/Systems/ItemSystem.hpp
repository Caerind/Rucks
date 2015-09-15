#ifndef ITEMSYSTEM_HPP
#define ITEMSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"

class ItemSystem : public es::System
{
    public:
        ItemSystem();

        static std::string getId();

        void update();
};

#endif // ITEMSYSTEM_HPP
