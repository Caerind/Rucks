#ifndef WORLD_HPP
#define WORLD_HPP

#include "../Aharos/Application.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/View.hpp>

#include "Packet.hpp"
#include "ChunkManager.hpp"

class World : public sf::Drawable
{
    public:
        World(ah::Application& application);
        ~World();

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool isOnline();

        ah::Application& getApplication();

        sf::View& getView();

    private:
        ah::Application& mApplication;

        sf::View mView;
};

#endif // WORLD_HPP
