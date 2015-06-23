#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class CollisionComponent : public es::Component
{
    public:
        CollisionComponent(sf::Vector2f const& size = sf::Vector2f(1,1));

        static std::string getId();

        void setSize(sf::Vector2f const& size);
        sf::Vector2f getSize() const;

        void move(sf::Vector2f const& movement);
        void setCenter(sf::Vector2f const& center);
        sf::Vector2f getCenter() const;

        sf::FloatRect getBounds() const;

        void render(sf::RenderTarget& target);

    private:
        sf::FloatRect mBounds;
};

void collision(sf::FloatRect const& rect, sf::Vector2f& movement);

#endif // COLLISIONCOMPONENT_HPP
