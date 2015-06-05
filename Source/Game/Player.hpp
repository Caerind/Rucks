#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity
{
    public:
        typedef std::shared_ptr<Player> Ptr;

        Player(World& world);

        static unsigned int getTypeId();

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        //Armor worn
        //Weapon worn
};

#endif // PLAYER_HPP
