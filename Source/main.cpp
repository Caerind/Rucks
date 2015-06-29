#include "../Lib/Aharos/Application.hpp"

#include "Configuration.hpp"
#include "World.hpp"

#include "States/GameState.hpp"

int main()
{
    // Load Config
    Configuration::instance().initialize();
    Configuration::instance().loadFromFile("Assets/Data/settings.conf");

    // Load Application
    ah::Application::instance().loadFont("Coolveticca","Assets/Fonts/Coolveticca.ttf");
    ah::Application::instance().showDebugScreen(true);
    ah::Application::instance().setFont(ah::Application::instance().getFont("Coolveticca"));
    ah::Application::instance().useConsole(true);

    // Window Config
    ah::Application::instance().create(sf::VideoMode(800,600),"Rucks");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");
    ah::Application::instance().setMouseCursorTexture("Assets/Textures/cursor.png");
    ah::Application::instance().useCustomMouseCursor();

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
