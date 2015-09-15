#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Aharos/Application/Application.hpp"
#include "../Aharos/Application/ResourceHolder.hpp"
#include "../Aharos/EntitySystem/EntityManager.hpp"
#include "../Aharos/Renderer/Renderer.hpp"

#include "Map/Map.hpp"
#include "Map/Orthogonal.hpp"
#include "Map/DefaultGen.hpp"

#include "Game/FactionManager.hpp"
#include "Game/Weapon.hpp"

#include "Systems.hpp"
#include "Components.hpp"
#include "Prefab.hpp"

class World : public Prefab
{
    public:
        typedef map::Map<map::Orthogonal,map::DefaultGen<map::Orthogonal>> WorldMap;

        static World& instance();

        void initialize();
        void terminate();

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void render(sf::RenderTarget& target);

        ah::ResourceHolder& getResources();
        es::EntityManager& getEntities();
        FactionManager& getFactions();

    private:
        World();
        ~World();

        static World mInstance;

        ah::ResourceHolder mResources;
        WorldMap mMap;
        FactionManager mFactions;
};

#endif // WORLD_HPP
