#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Lib/Aharos/ResourceHolder.hpp"
#include "../Lib/EntitySystem/EntitySystem.hpp"

#include "Chunk/ChunkManager.hpp"

#include "Server/Server.hpp"

class World : public sf::Drawable
{
    public:
        static World& instance();

        void initialize();
        void terminate();

        bool loadFromFile(std::string const& filename);
        bool saveToFile(std::string const& filename);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ah::ResourceHolder& getResources();
        sf::View& getView();
        ChunkManager& getChunks();
        es::EntityManager& getEntities();

        bool isOnline() const;
        bool isServer() const;

    private:
        World();
        ~World();

        static World mInstance;

        ah::ResourceHolder mResources;
        sf::View mView;
        ChunkManager mChunks;
        es::EntityManager mEntities;

        bool mIsOnline;
        bool mIsServer;

        Server mServer;
};

#endif // WORLD_HPP
