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
        CollisionComponent(sf::FloatRect const& rect);

        static std::string getId();

        void move(sf::Vector2f const& movement);
        void setCenter(sf::Vector2f const& center);
        sf::Vector2f getCenter() const;

        sf::FloatRect getCollisionBox() const;

        void renderCollisionBox(sf::RenderTarget& target);

    private:
        sf::FloatRect mBounds;
        sf::Vector2f mPosition;
};

#endif // COLLISIONCOMPONENT_HPP
