#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class LifeComponent : public es::Component
{
    public:
        LifeComponent(unsigned int life = 100, unsigned int lifeMax = 100);

        static std::string getId();

        void setLife(unsigned int life);
        void setLifeMax(unsigned int lifeMax);

        unsigned int getLife() const;
        unsigned int getLifeMax() const;

        bool isDead() const;
        bool isAlive() const;

        bool inflige(unsigned int damage); // return true if is has been killed by the damage
        bool restore(unsigned int heal); // return true if full life

    private:
        unsigned int mLife;
        unsigned int mLifeMax;
};

#endif // LIFECOMPONENT_HPP
