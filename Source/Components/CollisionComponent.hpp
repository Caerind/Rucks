#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class CollisionComponent : public es::Component, public sf::Drawable, public sf::Transformable
{
    public:
        CollisionComponent();

        static std::string getId();

        void setSize(float sizeX, float sizeY);
        void setSize(sf::Vector2f const& size);
        sf::Vector2f getSize() const;

        sf::FloatRect getBounds() const;
        bool intersects(sf::FloatRect const& rect) const;
        bool contains(sf::Vector2f const& pos) const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Vector2f mSize;
};

#endif // COLLISIONCOMPONENT_HPP
