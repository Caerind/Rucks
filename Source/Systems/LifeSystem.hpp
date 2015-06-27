#ifndef LIFESYSTEM_HPP
#define LIFESYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"
#include "../Components.hpp"

class LifeSystem : public es::System
{
    public:
        LifeSystem();

        static std::string getId();

        void update();
};

#endif // LIFESYSTEM_HPP