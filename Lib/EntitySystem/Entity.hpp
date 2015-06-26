#ifndef ES_ENTITY_HPP
#define ES_ENTITY_HPP

#include <cassert>
#include <memory>
#include <string>

#include "Component.hpp"
#include "EntityManager.hpp"

namespace es
{

class Entity
{
    public:
        friend class EntityManager;

        typedef std::shared_ptr<Entity> Ptr;

        Entity();

        template<typename T>
        T& addComponent(T* component = nullptr);

        template<typename T>
        bool hasComponent() const;
        bool hasComponent(std::string const& type) const;
        bool hasComponents(ComponentFilter const& filter) const;

        template<typename T>
        void removeComponent();
        void removeComponents();

        template<typename T>
        T& getComponent();

        std::size_t getId() const;
        EntityManager* getManager() const;
        bool hasManager() const;

    private:
        static std::size_t gIdCounter;

        std::size_t mId;
        EntityManager* mManager;
        ComponentArray mComponents;
};

template<typename T>
T& Entity::addComponent(T* component)
{
    if (component == nullptr)
    {
        component = new T();
    }
    component->mParent = this;
    mComponents[T::getId()] = component;

   if (hasManager())
   {
       mManager->updateEntity(mId,EntityManager::UpdateEntity::AddComponent);
   }

    return *component;
}

template<typename T>
bool Entity::hasComponent() const
{
    return mComponents.find(T::getId()) != mComponents.end();
}

template<typename T>
void Entity::removeComponent()
{
    auto itr = mComponents.find(T::getId());
    if (itr != mComponents.end())
    {
        mComponents.erase(itr);

        if (hasManager())
        {
            mManager->updateEntity(mId,EntityManager::UpdateEntity::RemoveComponent);
        }
    }
}

template<typename T>
T& Entity::getComponent()
{
    assert(hasComponent<T>());

    return static_cast<T&>(*mComponents[T::getId()]);
}


} // namespace es

#endif // ES_ENTITY_HPP
