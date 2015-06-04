#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class World;

class EntityManager : public sf::Drawable
{
    public:
        EntityManager(World& world);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        World& mWorld;
};

#endif // ENTITYMANAGER_HPP
