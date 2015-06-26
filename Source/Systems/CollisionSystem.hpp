#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../../Lib/EntitySystem/EntitySystem.hpp"
#include "../Components/Components.hpp"
#include "../Chunk/ChunkManager.hpp"
#include <SFML/System/Vector2.hpp>

class CollisionSystem : public es::System
{
    public:
        CollisionSystem();

        void setChunks(ChunkManager& chunks);

        static std::string getId();

        bool handle(es::Entity::Ptr e, sf::Vector2f& movement);
        bool projectileCollision(sf::FloatRect const& rect, es::Entity::Ptr& e);

    private:
        ChunkManager* mChunks;
};

#endif // COLLISIONSYSTEM_HPP
