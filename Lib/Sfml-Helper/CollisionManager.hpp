#ifndef SFH_COLLISIONMANAGER_HPP
#define SFH_COLLISIONMANAGER_HPP

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "CollisionShape.hpp"

namespace sfh
{

class CollisionManager : public sf::Drawable
{
    public:
        CollisionManager();

        void add(CollisionShape::Ptr shape);
        void remove(CollisionShape::Ptr shape);

        bool intersect(CollisionShape::Ptr shape);
        bool contains(sf::Vector2f point);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        std::vector<CollisionShape::Ptr> mCollisions;
};

CollisionManager::CollisionManager()
{
}

void CollisionManager::add(CollisionShape::Ptr shape)
{
    mCollisions.push_back(shape);
}

void CollisionManager::remove(CollisionShape::Ptr shape)
{
    for (auto itr = mCollisions.begin(); itr != mCollisions.end(); itr++)
    {
        if ((*itr) == shape)
        {
            mCollisions.erase(itr);
        }
    }
}

bool CollisionManager::intersect(CollisionShape::Ptr shape)
{
    if (shape == nullptr)
        return false;
    for (unsigned int i = 0; i < mCollisions.size(); i++)
        if (mCollisions[i] != nullptr)
            if (mCollisions[i]->intersect(shape))
                return true;
    return false;
}

bool CollisionManager::contains(sf::Vector2f point)
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        if (mCollisions[i] != nullptr)
        {
            if (mCollisions[i]->contains(point))
            {
                return true;
            }
        }
    }
    return false;
}

void CollisionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        target.draw(*mCollisions[i]);
    }
}


} // namespace sfh

#endif // SFH_COLLISIONMANAGER_HPP
