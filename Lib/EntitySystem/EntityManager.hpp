#ifndef ES_ENTITYMANAGER_HPP
#define ES_ENTITYMANAGER_HPP

#include <algorithm>
#include <memory>

namespace es
{

class Entity;
class System;

class EntityManager
{
    public:
        friend class Entity;
        friend class System;

        typedef std::shared_ptr<Entity> EntityPtr;
        typedef std::vector<EntityPtr> EntityArray;
        typedef std::vector<System*> SystemArray;

    public:
        EntityManager();

        EntityPtr create(std::string const& name = "");
        EntityPtr create(std::size_t id, std::string const& name = "");

        EntityPtr get(std::size_t id);
        EntityPtr getByName(std::string const& name);
        EntityArray getByType(std::string const& type);
        EntityArray getByTag(std::string const& tag);

        void remove(EntityPtr e);
        void remove(std::size_t id);
        void removeByName(std::string const& name);
        void removeByType(std::string const& type);
        void removeByTag(std::string const& tag);
        void removeAll();

        void addSystem(System* system);
        void removeSystem(System* system);

        std::size_t getEntitiesCount() const;

        bool idExist(std::size_t id) const;

    private:
        void updateAll();
        void update(std::size_t id);

    private:
        EntityArray mEntities;
        SystemArray mSystems;
};

}

#endif // ES_ENTITYMANAGER_HPP
