#include "ChunkManager.hpp"
#include "../World.hpp"
#include "../../Lib/Sfml-Helper/Utility.hpp"
#include "../../Lib/Sfml-Helper/Packet.hpp"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
    clear();
}

void ChunkManager::handleChunkPacket(sf::Packet& packet)
{
    sf::Vector2i pos;
    packet >> pos;
    for (unsigned int i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i].getPos() == pos)
        {
            mChunks[i].loadFromPacket(packet);
            return;
        }
    }
}

void ChunkManager::handleChunkModification(sf::Packet& packet)
{
    sf::Vector2i chunkPos, tilePos;
    unsigned int layer, id;
    packet >> chunkPos >> tilePos >> layer >> id;
    setId(chunkPos,tilePos,layer,id);
}

void ChunkManager::setId(sf::Vector2i cPos, sf::Vector2i tPos, unsigned int layer, unsigned int id)
{
    for (unsigned int i = 0; i < mChunks.size(); i++)
    {
        if (cPos == mChunks[i].getPos())
        {
            mChunks[i].setId(tPos,layer,id);
        }
    }
}

void ChunkManager::setId(sf::Vector2f pos, unsigned int layer, unsigned int id)
{
    sf::Vector2i cPos = worldToChunk(pos);
    sf::Vector2i tPos = worldToTile(pos);
    if (World::instance().isOnline() && !World::instance().isServer())
    {
        // TODO : Send Packet Modification
    }
    else
    {
        setId(cPos,tPos,layer,id);
    }
}

void ChunkManager::update(sf::View const& view)
{
    sf::FloatRect vRect = sfh::getViewRect(view);

    // Remove useless Chunks
    for (auto itr = mChunks.begin(); itr != mChunks.end(); itr++)
    {
        if (vRect.intersects(itr->getGlobalBounds()))
        {
            itr->resetTimer();
        }
        else if (itr->timerEnded())
        {
            if (!World::instance().isOnline() || World::instance().isServer())
            {
                itr->saveToFile();
            }
            mChunks.erase(itr);
        }
    }

    // Calc required Chunks
    std::array<sf::Vector2f,4> arrayF = sfh::getPoint<float>(vRect);
    std::array<sf::Vector2i,4> arrayI;
    for (unsigned int i = 0; i < arrayF.size(); i++)
    {
        arrayI[i] = worldToChunk(arrayF[i]);
    }
    sf::Vector2i pos;
    for (pos.x = arrayI[0].x; pos.x <= arrayI[2].x; pos.x++)
    {
        for (pos.y = arrayI[0].y; pos.y <= arrayI[2].y; pos.y++)
        {
            if (!contains(pos))
            {
                mChunks.emplace_back(pos);
            }
        }
    }
}

void ChunkManager::draw(sf::RenderTarget& target, sf::View const& view, unsigned int layer) const
{
    sf::FloatRect vRect = sfh::getViewRect(view);
    for (unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i].draw(target, vRect, layer);
    }
}

bool ChunkManager::contains(sf::Vector2i chunkPos)
{
    for (unsigned int i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i].getPos() == chunkPos)
        {
            return true;
        }
    }
    return false;
}

void ChunkManager::clear()
{
    for (unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i].saveToFile();
    }
    mChunks.clear();
}

sf::Vector2i ChunkManager::worldToChunk(sf::Vector2f pos)
{
    sf::Vector2i p;
    p.x = pos.x / Chunk::getChunkSize().x;
    if (pos.x < 0)
    {
        p.x--;
    }
    p.y = pos.y / Chunk::getChunkSize().y;
    if (pos.y < 0)
    {
        p.y--;
    }
    return p;
}

sf::Vector2i ChunkManager::worldToTile(sf::Vector2f pos)
{
    sf::Vector2i p;
    p.x = (pos.x / Chunk::getTileSize().x);
    p.y = (pos.y / Chunk::getTileSize().y);
    if (pos.x < 0)
    {
        p.x--;
    }
    if (pos.y < 0)
    {
        p.y--;
    }
    p.x %= Chunk::getChunkSizeTile().x;
    p.y %= Chunk::getChunkSizeTile().y;
    return p;
}
