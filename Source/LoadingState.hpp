#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "../Aharos/State.hpp"

class LoadingState : public ah::State
{
    public:
        LoadingState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // LOADINGSTATE_HPP
