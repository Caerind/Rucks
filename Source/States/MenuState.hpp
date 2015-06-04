#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../../Lib/Aharos/State.hpp"
#include "../../Lib/SimpleGui/SimpleGui.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

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

        void onActivate();
        void onDeactivate();

    private:
        void toPreGame();
        void toSettings();
        void quitGame();

    private:
        sf::RectangleShape mShape;

        sg::Container mContainer;
        sg::Box::Ptr mPregame;
        sg::Box::Ptr mSettings;
        sg::Box::Ptr mQuit;
};

#endif // MENUSTATE_HPP
