#ifndef CHUNKMANAGER_HPP
#define CHUNKMANAGER_HPP

#include <array>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include "Chunk.hpp"

class ChunkManager
{
    public:
        ChunkManager();
        ~ChunkManager();

        void handleChunkPacket(sf::Packet& packet);
        void handleChunkModification(sf::Packet& packet);

        void setId(sf::Vector2i cPos, sf::Vector2i tPos, unsigned int layer, unsigned int id);
        void setId(sf::Vector2f pos, unsigned int layer, unsigned int id);
        unsigned int getId(sf::Vector2i cPos, sf::Vector2i tPos, unsigned int layer);
        unsigned int getId(sf::Vector2f pos, unsigned int layer);

        void update(sf::View const& view);
        void draw(sf::RenderTarget& target, sf::View const& view, unsigned int layer) const;

        bool collision(sf::FloatRect const& rect, std::vector<sf::FloatRect>& rects);

        bool contains(sf::Vector2i chunkPos);
        void clear();

        static sf::Vector2i worldToChunk(sf::Vector2f pos);
        static sf::Vector2i worldToTile(sf::Vector2f pos);
        static sf::Vector2f toWorldPos(sf::Vector2i cPos, sf::Vector2i tPos);

    private:
        std::vector<Chunk> mChunks;
};

#endif // CHUNKMANAGER_HPP
