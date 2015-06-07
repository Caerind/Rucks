#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Text.hpp>

#include "Entity.hpp"

class Player : public Entity
{
    public:
        typedef std::shared_ptr<Player> Ptr;

        Player(World& world);

        static unsigned int getTypeId();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setName(std::string const& name);

    protected:
        sf::Text mTextName;
};

#endif // PLAYER_HPP
