#include "ChunkManager.hpp"
#include "World.hpp"
#include "OnlineManager.hpp"

ChunkManager::ChunkManager(World& world) : mWorld(world)
{
    sf::Vector2i m;
    for (m.x = -1; m.x < 2; m.x++)
    {
        for (m.y = -1; m.y < 2; m.y++)
        {
            mChunks[m.x+1][m.y+1] = std::make_shared<Chunk>(mWorld);
        }
    }
}

void ChunkManager::update()
{
    sf::Vector2i p = worldToChunk(mWorld.getView().getCenter());
    if (mChunks[1][1]->getPos() != p)
    {
        sf::Vector2i m;
        for (m.x = -1; m.x < 2; m.x++)
        {
            for (m.y = -1; m.y < 2; m.y++)
            {
                if (mWorld.isOnline())
                {
                    mChunks[m.x+1][m.y+1]->setPos(p+m);
                    mWorld.getOnlineManager().askChunk(p+m);
                }
                else
                {
                    mChunks[m.x+1][m.y+1]->load(p+m);
                }
            }
        }
    }
}

void ChunkManager::handleChunk(sf::Packet& packet)
{
    sf::Vector2i chunkPos;
    packet >> chunkPos;
    auto c = getChunk(chunkPos);
    if (c != nullptr)
        c->loadFromPacket(packet);
}

void ChunkManager::handleChunkModification(sf::Packet& packet)
{
    sf::Vector2i chunkPos, tilePos;
    unsigned int layer, id;
    packet >> chunkPos >> tilePos >> layer >> id;
    setId(chunkPos,tilePos,layer,id);
}

void ChunkManager::setId(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id)
{
    auto c = getChunk(chunkPos);
    if (c != nullptr)
        c->setTileId(tilePos,layer,id);
}

void ChunkManager::setId(sf::Vector2f pos, unsigned int layer, unsigned int id)
{
    sf::Vector2i chunkPos = worldToChunk(pos);
    sf::Vector2i tilePos = worldToTile(pos);
    auto c = getChunk(chunkPos);
    if (c != nullptr)
        c->setTileId(tilePos,layer,id);
}

void ChunkManager::render(sf::RenderTarget& target, unsigned int layer) const
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
        {
            if (mChunks[i][j] != nullptr)
            {
                if (sfh::isInView(mChunks[i][j]->getGlobalBounds(),mWorld.getView()))
                    mChunks[i][j]->render(target, layer);
            }
        }
}

sf::Vector2i ChunkManager::worldToChunk(sf::Vector2f pos)
{
    sf::Vector2i p;
    p.x = pos.x / Chunk::getChunkSizePx();
    if (pos.x < 0)
    {
        p.x--;
    }
    p.y = pos.y / Chunk::getChunkSizePx();
    if (pos.y < 0)
    {
        p.y--;
    }
    return p;
}

sf::Vector2i ChunkManager::worldToTile(sf::Vector2f pos)
{
    sf::Vector2i p;
    p.x = (pos.x / Chunk::getChunkSizeTile());
    p.y = (pos.y / Chunk::getChunkSizeTile());
    p.x %= Chunk::getChunkSizeTile();
    p.y %= Chunk::getChunkSizeTile();
    return p;
}

Chunk::Ptr ChunkManager::getChunk(sf::Vector2i pos)
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
            if (mChunks[i][j] != nullptr)
                if (mChunks[i][j]->getPos() == pos)
                    return mChunks[i][j];
    return nullptr;
}
