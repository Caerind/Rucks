#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include "PreGameState.hpp"
#include "SettingsState.hpp"

class MenuState : public ah::State
{
    public:
        MenuState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void toPreGame();
        void toSettings();
        void quitGame();

    private:
        sg::Container mContainer;
};

#endif // MENUSTATE_HPP
