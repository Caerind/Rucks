#ifndef APP_HPP
#define APP_HPP

#include "../../Lib/Aharos/Application.hpp"

#include "../States/IntroState.hpp"
#include "../States/MenuState.hpp"
#include "../States/SettingsState.hpp"
#include "../States/PreGameState.hpp"
#include "../States/LoadingState.hpp"
#include "../States/GameState.hpp"
#include "../States/PauseState.hpp"
#include "../States/EndState.hpp"

#include "../../Lib/Tools/gzstream.hpp"

#include "OnlineManager.hpp"

class App : public ah::Application
{
    public:
        static App& instance();

        OnlineManager& getOnlineManager();
        World& getWorld();

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
        World mWorld;
};

#endif // APP_HPP
