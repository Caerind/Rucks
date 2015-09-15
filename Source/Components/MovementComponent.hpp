#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"

#include <SFML/System/Vector2.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>

class MovementComponent : public es::Component
{
    public:
        MovementComponent();

        static std::string getId();

        void setSpeed(float speed);
        float getSpeed() const;

        void setDirection(sf::Vector2f const& direction);
        sf::Vector2f getDirection() const;

    private:
        float mSpeed;
        sf::Vector2f mDirection;
};

#endif // MOVEMENTCOMPONENT_HPP
