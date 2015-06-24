#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class TransformComponent : public es::Component, public sf::Transformable
{
    public:
        TransformComponent(float x = 0.f, float y = 0.f, float w = 0.f, float h = 0.f);
        TransformComponent(sf::Vector2f const& pos, sf::Vector2f const& size);

        static std::string getId();

        void setSize(sf::Vector2f const& size);
        sf::Vector2f getSize() const;

        sf::FloatRect getBoundingBox() const;

        void renderBoundingBox(sf::RenderTarget& target);

    private:
        sf::Vector2f mSize;
};

#endif // TRANSFORMCOMPONENT_HPP
