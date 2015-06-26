#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class LifeComponent : public es::Component, public sf::Drawable, public sf::Transformable
{
    public:
        LifeComponent(int life = 100, int lifeMax = 100);

        static std::string getId();

        void setLife(int life);
        void setLifeMax(int lifeMax);

        int getLife() const;
        int getLifeMax() const;

        void setLifePercent(float percent);
        float getLifePercent() const;

        bool isDead() const;
        bool isAlive() const;

        bool inflige(int damage); // return true if is has been killed by the damage
        bool restore(int heal); // return true if full life
        void fullRestore();

        void setLifeBarSize(sf::Vector2f const& lifeBarSize);
        sf::Vector2f getLifeBarSize() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        int mLife;
        int mLifeMax;

        sf::Vector2f mLifeBarSize;
};

#endif // LIFECOMPONENT_HPP
