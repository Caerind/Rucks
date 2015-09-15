#include "../Aharos/Application/Application.hpp"

#include "States/GameState.hpp"

#include "Configuration.hpp"

int main()
{
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

    Configuration::instance().initialize();

    // Register States
    ah::Application::instance().registerState<GameState>(GameState::getID());

    // Run
    ah::Application::instance().pushState(GameState::getID());
    ah::Application::instance().run();

    Configuration::instance().terminate();

    return EXIT_SUCCESS;
}
