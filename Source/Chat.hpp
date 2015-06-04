#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "../SimpleGui/SimpleGui.hpp"

class World;

class Chat : public sf::Drawable, public sf::Transformable
{
    public:
        Chat(World& world);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void add(std::string const& username, std::string const& message);

        void write(bool writing);
        bool isWriting() const;
        void send();

    private:
        void update();

    private:
        World& mWorld;

        sg::Container mContainer;
        sg::TextField::Ptr mTextField;

        std::vector<std::pair<sf::Text,sf::Clock>> mTexts;

        bool mWriting;
};

#endif // CHAT_HPP
