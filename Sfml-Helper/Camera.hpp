#ifndef SFH_CAMERA_HPP
#define SFH_CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sfh
{

sf::FloatRect getViewRect(sf::View const& view);

bool isInView(sf::FloatRect const& rect, sf::View const& view);

class Camera : public sf::View
{
    public:
        Camera();
        Camera(sf::FloatRect viewRect);
        Camera(sf::Vector2f center, sf::Vector2f size);
        Camera(sf::View view);

        void attachTo(sf::Transformable* target);
        void detach();

        void update();

        bool isIn(sf::FloatRect const& rect);
        sf::FloatRect getRect();

    private:
        sf::Transformable* mTarget;
};

} // namespace sfh

#endif // SFH_CAMERA_HPP
