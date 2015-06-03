#ifndef APP_HPP
#define APP_HPP

#include "../Aharos/Application.hpp"
#include "OnlineManager.hpp"

#include "IntroState.hpp"
#include "MenuState.hpp"
#include "SettingsState.hpp"
#include "PreGameState.hpp"
#include "LoadingState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"

class App : public ah::Application
{
    public:
        static App& instance();

        OnlineManager& getOnlineManager();

    private:
        void loadData();
        void loadLog();
        void loadLang();
        void loadWindow();
        void loadDebugScreen();
        void loadActionMap();
        void loadStateManager();

        App();
        ~App();

        static App mInstance;

        OnlineManager mOnlineManager;
};

#endif // APP_HPP
