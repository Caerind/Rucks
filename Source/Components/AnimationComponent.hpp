#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <cmath>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class AnimationComponent : public es::Component
{
    public:
        AnimationComponent();

        static std::string getId();

        enum Direction
        {
            N = 0,
            W,
            S,
            E,
        };

        void setSheetSize(sf::Vector2i const& sheetSize);
        sf::Vector2i getSheetSize() const;

        void setDirection(sf::Vector2f const& lookAt);
        void setDirection(Direction direction);
        Direction getDirection() const;
        sf::Vector2f getMovement() const;

        void addWalkTime(sf::Time dt);
        void resetWalkTime();
        sf::Time getWalkTime() const;

        void setWalkDuration(sf::Time duration);
        sf::Time getWalkDuration() const;

        static Direction getDirection(sf::Vector2f const& direction);

    private:
        sf::Vector2i mSheetSize;
        Direction mDirection;
        sf::Time mWalkTime;
        sf::Time mWalkDuration;
};

#endif // ANIMATIONCOMPONENT_HPP
