#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "../../Lib/Aharos/State.hpp"
#include "../../Lib/SimpleGui/SimpleGui.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class SettingsState : public ah::State
{
    public:
        SettingsState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void backState();

    private:
        sf::RectangleShape mShape;
        std::string mLastState;

        sg::Container mContainer;
        sg::Box::Ptr mBack;
};

#endif // SETTINGSSTATE_HPP
