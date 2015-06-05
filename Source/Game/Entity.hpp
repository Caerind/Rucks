#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"

class Entity : public GameObject
{
    public:
        typedef std::shared_ptr<Entity> Ptr;

        Entity(World& world);

        static unsigned int getTypeId();

        void setLife(unsigned int life);
        unsigned int getLife() const;

        void setLifeMax(unsigned int lifeMax);
        unsigned int getLifeMax() const;

    protected:
        unsigned int mLife;
        unsigned int mLifeMax;
};

#endif // ENTITY_HPP
