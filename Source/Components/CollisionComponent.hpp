#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Aharos/Renderer/Renderable.hpp"
#include "../../Aharos/Renderer/Renderer.hpp"

class CollisionComponent : public es::Component, public rd::Renderable, public sf::Transformable
{
    public:
        CollisionComponent();
        ~CollisionComponent();

        static std::string getId();

        void setSize(float sizeX, float sizeY);
        void setSize(sf::Vector2f const& size);
        sf::Vector2f getSize() const;

        sf::FloatRect getBounds();
        bool intersects(sf::FloatRect const& rect);
        bool contains(sf::Vector2f const& pos);

        void render(sf::RenderTarget& target);

        void setPosition(sf::Vector2f const& position);
        sf::Vector2f getPosition() const;

    private:
        sf::Vector2f mSize;
};

#endif // COLLISIONCOMPONENT_HPP
