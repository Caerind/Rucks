#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../../Lib/EntitySystem/EntitySystem.hpp"
#include "../Components/Components.hpp"
#include "../Chunk/ChunkManager.hpp"
#include <SFML/System/Vector2.hpp>

class CollisionSystem : public es::System
{
    public:
        CollisionSystem(ChunkManager& chunks);

        static std::string getId();

        bool handle(es::Entity::Ptr e, sf::Vector2f& movement);

    private:
        ChunkManager& mChunks;
};

#endif // COLLISIONSYSTEM_HPP
