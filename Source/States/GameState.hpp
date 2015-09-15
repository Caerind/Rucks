#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Aharos/Application/State.hpp"

#include "../World.hpp"

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();
};

#endif // GAMESTATE_HPP
