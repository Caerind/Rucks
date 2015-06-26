#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../Lib/EntitySystem/System.hpp"

#include "../Components.hpp"

class RenderSystem : public es::System
{
    public:
        RenderSystem();

        static std::string getId();

        void render(sf::RenderTarget& target);

        void renderDebug(bool renderDebug);

    private:
        bool mRenderDebug;
};

#endif // RENDERSYSTEM_HPP
