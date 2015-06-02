#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

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
        sg::Container mContainer;
        sf::RectangleShape mShape;
        std::string mLastState;
};

#endif // SETTINGSSTATE_HPP
