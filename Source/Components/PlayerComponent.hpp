#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class PlayerComponent : public es::Component
{
    public:
        PlayerComponent();

        static std::string getId();
};

#endif // PLAYERCOMPONENT_HPP
