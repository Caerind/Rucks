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
        SpriteComponent(std::string const& id = "", sf::Vector2i sheetSize = sf::Vector2i(1,1));

        static std::string getId();

        void setTexture(sf::Texture& texture);
        void setTexture(std::string const& id);
        void setTextureRect(sf::IntRect const& rect);
        void setSheetSize(sf::Vector2i sheetSize);

        sf::Vector2i getSheetSize() const;
        sf::Vector2i getTextureSize() const;
        sf::Vector2f getOrigin() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
        sf::Vector2i mSheetSize;
        sf::Vector2i mTextureSize;
};

#endif // SPRITECOMPONENT_HPP
