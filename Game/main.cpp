#include "Configuration.hpp"
#include "../Lib/Aharos/Application.hpp"

#include "States/GameState.hpp"

int main()
{
    // Load Config
    Configuration::instance().initialize();
    Configuration::instance().loadFromFile("Assets/Data/settings.conf");

    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"Rucks");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");

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

    // Save Config
    Configuration::instance().saveToFile("Data/settings.conf");
    Configuration::instance().terminate();

    return EXIT_SUCCESS;
}
