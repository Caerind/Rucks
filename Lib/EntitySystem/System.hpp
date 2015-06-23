#ifndef ES_SYSTEM_HPP
#define ES_SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

namespace es
{

class System
{
    public:
        typedef std::vector<Entity::Ptr> EntityArray;

    public:
        System();
        System(EntityManager* manager);
        virtual ~System();

        void add(Entity::Ptr e);
        void remove(Entity::Ptr e);
        void removeAll();
        bool contains(Entity::Ptr e);
        bool hasRequiredComponents(Entity::Ptr e);
        EntityArray getEntities();

    protected:
        EntityManager* mManager;
        EntityArray mEntities;
        ComponentFilter mFilter;
};

}

#endif // ES_SYSTEM_HPP
