#include "../Lib/Aharos/Application.hpp"

#include "Configuration.hpp"
#include "World.hpp"

#include "States/GameState.hpp"

int main()
{
    // Load Config
    Configuration::instance().initialize();
    Configuration::instance().loadFromFile("Assets/Data/settings.conf");

    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"Rucks");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");

    // Load Application

    //Register Actions
    ah::Application::instance().setAction("close",thor::Action(sf::Event::Closed));

    // Register Callbacks
    ah::Application::instance().bind("close",[&](ah::ActionTarget::Context context){context.window->close();});

    // Register States
    ah::Application::instance().registerState<GameState>(GameState::getID());

    // Load World
    World::instance().initialize();
    World::instance().loadFromFile("Assets/World/world.dat");

    // Run
    ah::Application::instance().pushState(GameState::getID());
    ah::Application::instance().run();

    // Save World
    World::instance().saveToFile("Assets/World/world.dat");
    World::instance().terminate();

    // Save Config
    Configuration::instance().saveToFile("Assets/Data/settings.conf");
    Configuration::instance().terminate();

    return EXIT_SUCCESS;
}
