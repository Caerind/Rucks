#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class SpriteComponent : public es::Component, public sf::Drawable
{
    public:
        SpriteComponent(std::string const& id = "");

        static std::string getId();

        void setTexture(sf::Texture& texture);
        void setTexture(std::string const& id);
        void setTextureRect(sf::IntRect const& rect);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
};

#endif // SPRITECOMPONENT_HPP
