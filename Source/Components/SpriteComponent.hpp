#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"

#include "../../Aharos/Renderer/Sprite.hpp"
#include "../../Aharos/Renderer/Renderer.hpp"

class SpriteComponent : public es::Component, public rd::Sprite
{
    public:
        SpriteComponent(std::string const& id = "");
        ~SpriteComponent();

        static std::string getId();

        void setTexture(std::string const& id);
        sf::Vector2u getTextureSize() const;
        void render(sf::RenderTarget& target);
        sf::FloatRect getBounds();
};

#endif // SPRITECOMPONENT_HPP
