#ifndef SFH_EVENT_HPP_INCLUDED
#define SFH_EVENT_HPP_INCLUDED

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <ctime>

namespace sfh
{

void handleZoom(sf::Event const& event, sf::View& view, float delta);
void handleScreenshot(sf::Event const& event, sf::Keyboard::Key key, sf::RenderWindow& window, std::string path = "");



///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


void handleZoom(sf::Event const& event, sf::View& view, float delta)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        if (event.mouseWheel.delta < 1)
        {
            view.zoom(1.f + delta);
        }
        else
        {
            view.zoom(1.f - delta);
        }
    }
}

void handleScreenshot(sf::Event const& event, sf::Keyboard::Key key, sf::RenderWindow& window, std::string path)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == key)
        {
            time_t rawtime;
            struct tm* timeinfo;
            char buffer[80];
            time (&rawtime);
            timeinfo = localtime(&rawtime);
            std::string timeFormat = "%d-%m-%y_%H-%M-%S";
            strftime(buffer,80,timeFormat.c_str(),timeinfo);
            window.capture().saveToFile(path + std::string(buffer) + ".png");
        }
    }
}




} // namespace sfh

#endif // SFH_EVENT_HPP_INCLUDED
