#ifndef ITEMSYSTEM_HPP
#define ITEMSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

#include <Thor/Math/Random.hpp>

class ItemSystem : public es::System
{
    public:
        ItemSystem();

        static std::string getId();

        void update();
};

#endif // ITEMSYSTEM_HPP
