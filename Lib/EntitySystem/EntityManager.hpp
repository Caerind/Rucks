#ifndef ES_ENTITYMANAGER_HPP
#define ES_ENTITYMANAGER_HPP

#include <algorithm>
#include <map>
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
        typedef std::map<std::string,System*> SystemArray;

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

        template<typename T>
        T& addSystem(T* system);

        template<typename T>
        bool hasSystem();
        bool hasSystem(std::string const& type);

        template<typename T>
        void removeSystem();
        void removeAllSystems();

        template<typename T>
        T& getSystem();

        std::size_t getEntitiesCount() const;

        bool idExist(std::size_t id) const;

    private:
        void updateAll();
        void update(std::size_t id);

    private:
        EntityArray mEntities;
        SystemArray mSystems;
};

template<typename T>
T& EntityManager::addSystem(T* system)
{
    system->setManager(this);
    mSystems[T::getId()] = system;
    updateAll();
    return *system;
}

template<typename T>
bool EntityManager::hasSystem()
{
    return mSystems.find(T::getId()) != mSystems.end();
}

template<typename T>
void EntityManager::removeSystem()
{
    if (hasSystem<T>())
    {
        mSystems.erase(mSystems.find(T::getId()));
        updateAll();
    }
}

template<typename T>
T& EntityManager::getSystem()
{
    assert(hasSystem<T>());

    return static_cast<T&>(*mSystems[T::getId()]);
}

}

#endif // ES_ENTITYMANAGER_HPP
