#include "Packet.hpp"

sf::Packet& operator <<(sf::Packet& packet, const sf::Color& c)
{
	return packet << c.r << c.g << c.b << c.a;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Color& c)
{
	return packet >> c.r >> c.g >> c.b >> c.a;
}
