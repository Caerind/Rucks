#ifndef PLAYERINPUTCOMPONENT_HPP
#define PLAYERINPUTCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class PlayerInputComponent : public es::Component
{
    public:
        PlayerInputComponent();

        static std::string getId();
};

#endif // PLAYERINPUTCOMPONENT_HPP
