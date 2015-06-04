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


} // namespace sfh

#endif // SFH_EVENT_HPP_INCLUDED
