#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class MovementComponent : public es::Component
{
    public:
        MovementComponent(float speed = 100.f);

        static std::string getId();

        void setSpeed(float speed);
        float getSpeed() const;

        void setLastMovement(sf::Vector2f movement);
        sf::Vector2f getLastMovement() const;

        void setLookAt(sf::Vector2f lookAt);
        sf::Vector2f getLookAt() const;

        void resetWalkTime();
        void addWalkTime(sf::Time dt);
        sf::Time getWalkTime() const;

    private:
        float mSpeed;
        sf::Vector2f mLastMovement;
        sf::Vector2f mLookAt;
        sf::Time mWalkTime;
};

#endif // MOVEMENTCOMPONENT_HPP
