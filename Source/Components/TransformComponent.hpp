#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class TransformComponent : public es::Component, public sf::Transformable
{
    public:
        TransformComponent(float x = 0.f, float y = 0.f);
        TransformComponent(sf::Vector2f const& pos);

        static std::string getId();
};

#endif // TRANSFORMCOMPONENT_HPP
