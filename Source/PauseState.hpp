#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "../Aharos/State.hpp"

class PauseState : public ah::State
{
    public:
        PauseState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PAUSESTATE_HPP
