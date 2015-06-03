#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "../Aharos/State.hpp"
#include "../SimpleGui/SimpleGui.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "MenuState.hpp"

class EndState : public ah::State
{
    public:
        EndState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void toMenu();

    private:
        sf::RectangleShape mShape;

        sg::Container mContainer;
        sg::Box::Ptr mMenu;
};


#endif // ENDSTATE_HPP
