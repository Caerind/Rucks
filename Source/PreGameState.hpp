#ifndef PREGAMESTATE_HPP
#define PREGAMESTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include "MenuState.hpp"
#include "LoadingState.hpp"

class PreGameState : public ah::State
{
    public:
        PreGameState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void toLoading();
        void toMenu();

    private:
        sg::Container mContainer;
};

#endif // PREGAMESTATE_HPP
