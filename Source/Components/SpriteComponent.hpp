#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "../../Lib/EntitySystem/Component.hpp"

class SpriteComponent : public es::Component, public sf::Sprite
{
    public:
        SpriteComponent(std::string const& id = "", sf::Vector2i sheetSize = sf::Vector2i(1,1));

        static std::string getId();

        void setTexture(std::string const& id);
        void setSheetSize(sf::Vector2i sheetSize);

        sf::Vector2i getSheetSize() const;
        sf::Vector2i getTextureSize() const;

    private:
        sf::Vector2i mSheetSize;
};

#endif // SPRITECOMPONENT_HPP
