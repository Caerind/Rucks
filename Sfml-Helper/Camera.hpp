#ifndef SFH_CAMERA_HPP
#define SFH_CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sfh
{

sf::FloatRect getViewRect(sf::View const& view)
{
    return sf::FloatRect(view.getCenter()-view.getSize()*0.5f,view.getSize());
}

bool isInView(sf::FloatRect const& rect, sf::View const& view)
{
    return rect.intersects(getViewRect(view));
}


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


Camera::Camera() : sf::View()
{
    mTarget = nullptr;
}

Camera::Camera(sf::FloatRect viewRect) : sf::View(viewRect)
{
    mTarget = nullptr;
}

Camera::Camera(sf::Vector2f center, sf::Vector2f size) : sf::View(center,size)
{
    mTarget = nullptr;
}

Camera::Camera(sf::View view) : sf::View(view.getCenter(),view.getSize())
{
    mTarget = nullptr;
}

void Camera::attachTo(sf::Transformable* target)
{
    mTarget = target;
}

void Camera::detach()
{
    mTarget = nullptr;
}

void Camera::update()
{
    if (mTarget != nullptr)
    {
        setCenter(mTarget->getPosition());
    }
}

bool Camera::isIn(sf::FloatRect const& rect)
{
    return isInView(rect,*this);
}

sf::FloatRect Camera::getRect()
{
    return getViewRect(*this);
}


} // namespace sfh

#endif // SFH_CAMERA_HPP
