#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../../Lib/Aharos/State.hpp"

#include <map>
#include <Thor/Input/Connection.hpp>

#include "PauseState.hpp"
#include "EndState.hpp"

#include "../Game/World.hpp"

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);

        typedef thor::ActionContext<std::string> tContext;

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

    private:
        void toPause();
        void toEnd();

    private:
        World& mWorld;
        std::map<std::string,thor::Connection> mConnections;
};

#endif // GAMESTATE_HPP
