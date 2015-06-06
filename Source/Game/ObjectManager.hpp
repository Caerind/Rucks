#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "GameObject.hpp"
#include "Player.hpp"

class World;

class ObjectManager : public sf::Drawable
{
    public:
        ObjectManager(World& world);

        GameObject::Ptr createGameObject(unsigned int id);
        Entity::Ptr createEntity(unsigned int id);
        Player::Ptr createPlayer(unsigned int id);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setPlayerId(unsigned int id);
        unsigned int getPlayerId() const;

        void remove(unsigned int id);

        GameObject::Ptr getGameObject(unsigned int id);
        Entity::Ptr getEntity(unsigned int id);
        Player::Ptr getPlayer(unsigned int id);
        Player::Ptr getPlayer();

    protected:
        World& mWorld;

        std::vector<GameObject::Ptr> mGameObjects;

        std::vector<Entity::Ptr> mEntities;
        std::vector<Player::Ptr> mPlayers;

        unsigned int mPlayerId;
};

#endif // OBJECTMANAGER_HPP
