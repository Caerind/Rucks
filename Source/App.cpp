#include "App.hpp"

App App::mInstance;

App& App::instance()
{
    return mInstance;
}

void App::loadData()
{
    //ah::DataManager::setData("sound-name","Example/explosion.wav");
    //ah::DataManager::setData<float>("speed-x",75.f);
}

void App::loadLog()
{
    ah::Log::openLog("Assets/Log/0.log");
}

void App::loadLang()
{
}

void App::loadWindow()
{
    ah::Window::create(sf::VideoMode(800,600),"Rucks",sf::Style::Close);

    ah::Window::setIcon("Assets/Textures/icon.png");

    ah::Window::setMouseCursorTexture("Assets/Textures/cursor.png");
    ah::Window::useCustomMouseCursor();
}

void App::loadDebugScreen()
{
    ah::DebugScreen::setFont(ah::ResourceHolder::getFont("Assets/Fonts/sansation.ttf"));
    ah::DebugScreen::setCharsize(20);
    ah::DebugScreen::hideDebugScreen();
}

void App::loadActionMap()
{
    // Close
    mActionMap["close"] = thor::Action(sf::Event::Closed);
    mCallbackSystem.connect("close",[&](thor::ActionContext<std::string> context){close();});

    // DebugScreen
    mActionMap["toggledebugscreen"] = thor::Action(sf::Keyboard::F2, thor::Action::PressOnce);
    mCallbackSystem.connect("toggledebugscreen",[&](thor::ActionContext<std::string> context){
        if (isDebugScreenVisible())
        {
            hideDebugScreen();
        }
        else
        {
            showDebugScreen();
        }
    });

    // Screenshot
    mActionMap["screenshot"] = thor::Action(sf::Keyboard::F1, thor::Action::PressOnce);
    mCallbackSystem.connect("screenshot",[&](thor::ActionContext<std::string> context){
        capture().saveToFile("Assets/Screenshots/" + ah::getTime("%d-%m-%y_%H-%M-%S") + ".png");
    });
}

void App::loadStateManager()
{
    registerState<IntroState>(IntroState::getID());
    registerState<MenuState>(MenuState::getID());
    registerState<SettingsState>(SettingsState::getID());
    registerState<PreGameState>(PreGameState::getID());
    registerState<LoadingState>(LoadingState::getID());
    registerState<GameState>(GameState::getID());
    registerState<PauseState>(PauseState::getID());

    pushState(IntroState::getID());
}

App::App() : ah::Application()
{
    loadData();
    loadLog();
    loadLang();
    loadWindow();
    loadDebugScreen();
    loadActionMap();
    loadStateManager();
}

App::~App()
{
}
