#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <memory>
#include <array>
#include <fstream>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/Packet.hpp>

#include <Thor/Math/Random.hpp>

class World;

class Chunk : public sf::Transformable
{
    public:
        Chunk(World& world);
        ~Chunk();

        typedef std::shared_ptr<Chunk> Ptr;

        void load(sf::Vector2i pos);
        void loadFromPacket(sf::Packet& packet);
        void loadInPacket(sf::Packet& packet);

        void setPos(sf::Vector2i pos);
        sf::Vector2i getPos() const;

        void setTileId(sf::Vector2i tilePos, unsigned int layer, unsigned int id);
        unsigned int getTileId(sf::Vector2i tilePos, unsigned int layer);

        void render(sf::RenderTarget& target, unsigned int layer) const;

        sf::FloatRect getGlobalBounds() const;

        static unsigned int getChunkSizePx();
        static unsigned int getChunkSizeTile();
        static unsigned int getTileSize();

    private:
        bool loadFromFile();
        void saveToFile();
        void generate();
        std::string posToStr();

        unsigned int texCoordsToId(sf::Vector2f texCoords);
        sf::Vector2f idToTexCoords(unsigned int id);
        unsigned int getTilesPerLine();

    protected:
        World& mWorld;
        sf::Texture& mTexture;

        std::array<sf::VertexArray,3> mLayers;

        sf::Vector2i mPos;
};

#endif // CHUNK_HPP
