#ifndef PLAYERCONTROLLERSYSTEM_HPP
#define PLAYERCONTROLLERSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"

#include "../Components.hpp"
#include "../Configuration.hpp"

#include "../../Aharos/Application/ActionTarget.hpp"
#include "../../Aharos/Application/Application.hpp"

#include "../../Aharos/Renderer/Renderer.hpp"

class PlayerControllerSystem : public es::System, public ah::ActionTarget
{
    public:
        PlayerControllerSystem();

        static std::string getId();

        void update();

        es::Entity::Ptr getTarget(sf::Vector2f const& position);
};

#endif // PLAYERCONTROLLERSYSTEM_HPP
