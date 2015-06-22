#include "Lib/Aharos/Application.hpp"

#include "Game/States/GameState.hpp"

int main()
{
    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"Rucks");

    // ...

    //Register Actions
    ah::Application::instance().setAction("close",thor::Action(sf::Event::Closed));

    // Register Callbacks
    ah::Application::instance().bind("close",[&](ah::ActionTarget::Context context){context.window->close();});

    // Register States
    ah::Application::instance().registerState<GameState>(GameState::getID());

    // Run
    ah::Application::instance().pushState(GameState::getID());
    ah::Application::instance().run();
    return EXIT_SUCCESS;
}
