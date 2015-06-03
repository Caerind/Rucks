#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include "GameState.hpp"

class LoadingState : public ah::State
{
    public:
        LoadingState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void toGame();

    private:
        sg::Container mContainer;
};

#endif // LOADINGSTATE_HPP
