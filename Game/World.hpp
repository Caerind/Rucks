#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Lib/Aharos/ResourceHolder.hpp"

class World : public sf::Drawable
{
    public:
        static World& instance();

        void initialize();
        void terminate();

        bool loadFromFile(std::string const& filename);
        bool saveToFile(std::string const& filename);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ah::ResourceHolder& getResources();
        sf::View& getView();

        bool isOnline() const;
        bool isServer() const;

    private:
        World();
        ~World();

        static World mInstance;

        ah::ResourceHolder mResources;
        sf::View mView;

        bool mOnline;
        bool mServer;
};

#endif // WORLD_HPP
