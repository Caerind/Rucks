#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Transformable.hpp>

class TransformComponent : public es::Component, public sf::Transformable
{
    public:
        TransformComponent(sf::Vector2f const& position = sf::Vector2f(), sf::Vector2f const& origin = sf::Vector2f());

        static std::string getId();
};

#endif // TRANSFORMCOMPONENT_HPP
