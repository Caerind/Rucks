#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"

class PlayerComponent : public es::Component
{
    public:
        PlayerComponent();

        static std::string getId();
};

#endif // PLAYERCOMPONENT_HPP
