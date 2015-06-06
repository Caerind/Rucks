#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"

class Entity : public GameObject
{
    public:
        typedef std::shared_ptr<Entity> Ptr;

        Entity(World& world);

        static unsigned int getTypeId();

    protected:
};

#endif // ENTITY_HPP
