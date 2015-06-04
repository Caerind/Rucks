#ifndef PREGAMESTATE_HPP
#define PREGAMESTATE_HPP

#include "../../Lib/Aharos/State.hpp"
#include "../../Lib/SimpleGui/SimpleGui.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

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
        sf::RectangleShape mShape;

        sg::Container mContainer;
        sg::TextField::Ptr mAddress;
        sg::TextField::Ptr mUsername;
        sg::Box::Ptr mLoading;
        sg::Box::Ptr mMenu;
};

#endif // PREGAMESTATE_HPP
