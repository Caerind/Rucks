#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class MovementComponent : public es::Component
{
    public:
        MovementComponent(float speed = 100.f);

        enum Direction
        {
            N,
            W,
            S,
            E,
        };

        static std::string getId();

        void setSpeed(float speed);
        float getSpeed() const;

        void setDirection(Direction direction);
        void setDirection(sf::Vector2f const& position, sf::Vector2f const& lookAt);
        Direction getDirection() const;

        void lastMovement(sf::Vector2f const& movement, sf::Time dt);
        void stopWalking();
        void walking(sf::Time dt);
        sf::Time getWalkTime() const;

        void update(sf::Time dt, sf::Vector2f const& movement, sf::Vector2f const& position, sf::Vector2f const& lookAt);

    private:
        float mSpeed;
        Direction mDirection;
        sf::Time mWalkTime;
};

#endif // MOVEMENTCOMPONENT_HPP
