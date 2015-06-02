#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include "MenuState.hpp"

class IntroState : public ah::State
{
    public:
        IntroState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void toMenu();

    private:
        sg::Container mContainer;
};

#endif // INTROSTATE_HPP
