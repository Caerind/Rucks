#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <SFML/System/Vector2.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class TransformComponent : public es::Component
{
    public:
        TransformComponent(float x = 0.f, float y = 0.f);
        TransformComponent(sf::Vector2f pos);

        static std::string getId();

        void setPosition(float x, float y);
        void move(float x, float y);

        void setPosition(sf::Vector2f pos);
        void move(sf::Vector2f movement);

        sf::Vector2f getPosition() const;

    private:
        sf::Vector2f mPosition;
};

#endif // TRANSFORMCOMPONENT_HPP
