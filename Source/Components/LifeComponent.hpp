#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class LifeComponent : public es::Component
{
    public:
        LifeComponent(int life = 100, int lifeMax = 100);

        static std::string getId();

        void setLife(int life);
        void setLifeMax(int lifeMax);

        int getLife() const;
        int getLifeMax() const;

        bool isDead() const;
        bool isAlive() const;

        bool inflige(int damage); // return true if is has been killed by the damage
        bool restore(int heal); // return true if full life

        void renderLifeBar(sf::RenderTarget& target, sf::RenderStates states);

    private:
        int mLife;
        int mLifeMax;
};

#endif // LIFECOMPONENT_HPP
