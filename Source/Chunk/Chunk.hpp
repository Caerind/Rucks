#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <array>
#include <fstream> // TODO : json ?

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "../../Lib/Aharos/String.hpp"

class Chunk
{
    public:
        Chunk(sf::Vector2i pos);
        ~Chunk();

        void resetTimer();
        bool timerEnded() const;

        bool loadFromFile();
        void generate();
        void saveToFile();

        void loadFromPacket(sf::Packet& packet);
        void writeToPacket(sf::Packet& packet);

        void setId(sf::Vector2i tPos, unsigned int layer, unsigned int id);
        unsigned int getId(sf::Vector2i tPos, unsigned int layer);

        void draw(sf::RenderTarget& target, sf::FloatRect const& rect, unsigned int layer) const;

        sf::Vector2i getPos() const;
        sf::FloatRect getGlobalBounds() const;

        static sf::Vector2i getTileSize();
        static sf::Vector2i getChunkSize();
        static sf::Vector2i getChunkSizeTile();
        static sf::Time getReleaseTime();
        static std::string getFilenameFromPos(sf::Vector2i pos);

        unsigned int texCoordsToId(sf::Vector2f texCoords);
        sf::Vector2f idToTexCoords(unsigned int id);
        unsigned int getTilesPerLine();

    private:
        sf::Clock mClock;
        sf::RenderStates mStates;
        sf::Vector2i mPos;
        std::array<sf::VertexArray,3> mLayers;
        sf::Vector2u mTextureSize;
};

#endif // CHUNK_HPP
