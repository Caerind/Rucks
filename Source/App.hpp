#ifndef APP_HPP
#define APP_HPP

#include "../Aharos/Application.hpp"

#include "IntroState.hpp"
#include "MenuState.hpp"
#include "SettingsState.hpp"
#include "PreGameState.hpp"
#include "LoadingState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

class App : public ah::Application
{
    public:
        static App& instance();

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
};

#endif // APP_HPP
