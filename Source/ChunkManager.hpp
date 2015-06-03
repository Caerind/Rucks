#ifndef CHUNKMANAGER_HPP
#define CHUNKMANAGER_HPP

#include "Chunk.hpp"
#include <array>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Sfml-Helper/Camera.hpp"
#include "../Sfml-Helper/Packet.hpp"

class World;

class ChunkManager
{
    public:
        ChunkManager(World& world);

        void update();

        void handleChunk(sf::Packet& packet);
        void handleChunkModification(sf::Packet& packet);

        void setId(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id);
        void setId(sf::Vector2f pos, unsigned int layer, unsigned int id);

        void render(sf::RenderTarget& target, unsigned int layer) const;

        static sf::Vector2i worldToChunk(sf::Vector2f pos);
        static sf::Vector2i worldToTile(sf::Vector2f pos);

    protected:
        Chunk::Ptr getChunk(sf::Vector2i pos);


    protected:
        World& mWorld;

        std::array<std::array<Chunk::Ptr,3>,3> mChunks;
};

#endif // CHUNKMANAGER_HPP
