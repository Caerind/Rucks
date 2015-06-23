#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/CollisionComponent.hpp"

class RenderSystem : public es::System
{
    public:
        RenderSystem();

        static std::string getId();

        void render(sf::RenderTarget& target);
};

#endif // RENDERSYSTEM_HPP
