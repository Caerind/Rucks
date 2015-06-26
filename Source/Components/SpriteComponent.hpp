#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SpriteComponent : public es::Component, public sf::Sprite
{
    public:
        SpriteComponent(std::string const& id = "");

        static std::string getId();

        void setTexture(std::string const& id);
        sf::Vector2u getTextureSize() const;
};

#endif // SPRITECOMPONENT_HPP
