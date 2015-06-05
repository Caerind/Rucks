#include "App.hpp"

App App::mInstance;

App& App::instance()
{
    return mInstance;
}

OnlineManager& App::getOnlineManager()
{
    return mOnlineManager;
}

World& App::getWorld()
{
    return mWorld;
}

void App::loadData()
{
    {
        igzstream file("Assets/Data/network.properties");
        if (file)
        {
            std::string temp;

            std::getline(file,temp);
            ah::DataManager::setData("ip",temp);

            std::getline(file,temp);
            ah::DataManager::setData("username",temp);

            std::getline(file,temp);
            ah::DataManager::setData("port",temp);
        }
        file.close();
    }
}

void App::loadLog()
{
    ah::Log::openLog("Assets/Log/0.log");
    ah::Log::useConsole(true);
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
    mActionMap["close"] = thor::Action(sf::Event::Closed);
    mActionMap["toggledebugscreen"] = thor::Action(sf::Keyboard::F2,thor::Action::PressOnce);
    mActionMap["screenshot"] = thor::Action(sf::Keyboard::F1,thor::Action::PressOnce);
    mActionMap["pause"] = thor::Action(sf::Keyboard::Escape,thor::Action::PressOnce);
    mActionMap["writing"] = thor::Action(sf::Keyboard::T,thor::Action::PressOnce);
    mActionMap["sendMessage"] = thor::Action(sf::Keyboard::Return,thor::Action::PressOnce);
    mActionMap["up"] = thor::Action(sf::Keyboard::Z,thor::Action::Hold);
    mActionMap["left"] = thor::Action(sf::Keyboard::Q,thor::Action::Hold);
    mActionMap["down"] = thor::Action(sf::Keyboard::S,thor::Action::Hold);
    mActionMap["right"] = thor::Action(sf::Keyboard::D,thor::Action::Hold);

    // Close
    mCallbackSystem.connect("close",[&](thor::ActionContext<std::string> context){instance().getOnlineManager().disconnect();close();});

    // DebugScreen
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
    mCallbackSystem.connect("screenshot",[&](thor::ActionContext<std::string> context){
        App::instance().capture().saveToFile("Assets/Screenshots/" + ah::getTime("%d-%m-%y_%H-%M-%S") + ".png");
        App::instance() << "Screenshot saved !";
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
    registerState<EndState>(EndState::getID());

    pushState(IntroState::getID());
}

App::App() : ah::Application(), mWorld(true)
{
    loadLog();
    loadData();
    loadLang();
    loadWindow();
    loadDebugScreen();
    loadActionMap();
    loadStateManager();
}

App::~App()
{
    {
        ogzstream file("Assets/Data/network.properties");
        if (file)
        {
            file << ah::DataManager::getData<std::string>("ip") << std::endl;
            file << ah::DataManager::getData<std::string>("username") << std::endl;
            file << ah::DataManager::getData<std::string>("port") << std::endl;
        }
        file.close();
    }
}
