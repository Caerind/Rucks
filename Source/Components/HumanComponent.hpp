#ifndef HUMANCOMPONENT_HPP
#define HUMANCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"

#include "../../Aharos/Renderer/Renderable.hpp"
#include "../../Aharos/Renderer/Renderer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class HumanComponent : public es::Component, public rd::Renderable
{
    public:
        HumanComponent();
        ~HumanComponent();

        enum Direction
        {
            N = 0,
            W,
            S,
            E,
        };

        static std::string getId();

        void setTextureRect(sf::IntRect const& tRect);
        void setBodyTextureRect(sf::IntRect const& tRect);
        void setRightArmTextureRect(sf::IntRect const& tRect);
        void setLeftArmTextureRect(sf::IntRect const& tRect);

        void setLeftArmTexture(std::string const& id);

        sf::FloatRect getBounds();
        void render(sf::RenderTarget& target);
        void setPosition(sf::Vector2f const& position);
        sf::Vector2f getPosition() const;

        void setDirection(sf::Vector2f const& lookAt);
        void setDirection(Direction direction);
        Direction getDirection() const;
        sf::Vector2f getMovement() const;
        static Direction getDirection(sf::Vector2f const& direction);

        void addWalkTime(sf::Time dt);
        void resetWalkTime();
        sf::Time getWalkTime() const;

        sf::Time getWalkDuration() const;
        sf::Time getCastDuration() const;
        sf::Vector2i getSheetSize() const;
        sf::Vector2u getTextureSize() const;

    private:
        Direction mDirection;
        sf::Time mWalkTime;
        sf::Time mWalkDuration;

        sf::Sprite mRightArm;
        sf::Sprite mLeftArm;
        sf::Sprite mBody;
        sf::Sprite mLegs;
};

#endif // HUMANCOMPONENT_HPP
