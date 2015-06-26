#ifndef PLAYERCONTROLLERSYSTEM_HPP
#define PLAYERCONTROLLERSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

#include "../../Lib/Aharos/ActionTarget.hpp"

class PlayerControllerSystem : public es::System, public ah::ActionTarget
{
    public:
        PlayerControllerSystem();

        static std::string getId();

        void update();
};

#endif // PLAYERCONTROLLERSYSTEM_HPP
