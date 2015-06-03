#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "EndState.hpp"
#include "GameState.hpp"
#include "SettingsState.hpp"

class PauseState : public ah::State
{
    public:
        PauseState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

    private:
        void toGame();
        void toSettings();
        void toEnd();

    private:
        sf::RectangleShape mShape;

        sg::Container mContainer;
        sg::Box::Ptr mGame;
        sg::Box::Ptr mSettings;
        sg::Box::Ptr mEnd;
};

#endif // PAUSESTATE_HPP
