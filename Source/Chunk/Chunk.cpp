#include "Chunk.hpp"
#include "../World.hpp"
#include <Thor/Math/Random.hpp>

std::vector<unsigned int> Chunk::mCollisionIds = Chunk::initializeCollisions();

Chunk::Chunk(sf::Vector2i pos)
{
    mPos = pos;

    sf::Transformable t;
    t.setPosition(mPos.x * getChunkSize().x, mPos.y * getChunkSize().y);
    mStates.transform = t.getTransform();

    sf::Texture& texture = World::instance().getResources().getTexture("tileset");
    mTextureSize = texture.getSize();
    mStates.texture = &texture;

    for (unsigned int i = 0; i < mLayers.size(); i++)
    {
        mLayers[i].resize(getChunkSizeTile().x * getChunkSizeTile().y * 4);
        mLayers[i].setPrimitiveType(sf::Quads);
    }

    if (!World::instance().isOnline() || World::instance().isServer())
    {
        if (!loadFromFile())
        {
            generate();
        }
    }
    else
    {
        // TODO (#9#): Send Packet Require Chunk
    }
}

Chunk::~Chunk()
{
}

void Chunk::resetTimer()
{
    mClock.restart();
}

bool Chunk::timerEnded() const
{
    return mClock.getElapsedTime() >= getReleaseTime();
}

bool Chunk::loadFromFile()
{
    std::ifstream file(getFilenameFromPos(mPos));
    if (!file)
    {
        return false;
    }

    sf::Vector2i pos = sf::Vector2i(0,0);
    unsigned int l = 0;
    std::string line;
    while (std::getline(file,line))
    {
        std::stringstream ss1(line);
        std::string temp1;
        pos.x = 0;
        while (std::getline(ss1,temp1,';'))
        {
            std::stringstream ss2(temp1);
            std::string temp2;
            l = 0;
            while (std::getline(ss2,temp2,'-'))
            {
                unsigned int id;
                if (ah::from_string(temp2,id))
                    setId(pos,l,id);
                l++;
            }
            pos.x++;
        }
        pos.y++;
    }
    file.close();
    return true;
}

void Chunk::generate()
{
    // TODO (#8#): Better Generation Algorithm

    sf::Vector2i p;
    for (p.x = 0; p.x < getChunkSizeTile().x; p.x++)
    {
        for (p.y = 0; p.y < getChunkSizeTile().y; p.y++)
        {
            std::vector<unsigned int> ids;
            ids.push_back(181);
            ids.push_back(182);
            ids.push_back(183);
            ids.push_back(118);
            ids.push_back(310);
            ids.push_back(373);
            ids.push_back(374);
            ids.push_back(375);
            ids.push_back(800);
            ids.push_back(801);
            ids.push_back(802);
            ids.push_back(803);
            ids.push_back(804);
            int e = ids.size()-1;
            unsigned int id = ids[thor::random(0,e)];
            setId(p, 0, id);
        }
    }

    saveToFile();
}

void Chunk::saveToFile()
{
    std::ofstream file(getFilenameFromPos(mPos));
    if (file)
    {
        sf::Vector2i pos;
        for (pos.y = 0; pos.y < getChunkSizeTile().x; pos.y++)
        {
            for (pos.x = 0; pos.x < getChunkSizeTile().y; pos.x++)
            {
                file << getId(pos,0) << "-";
                file << getId(pos,1) << "-";
                file << getId(pos,2) << ";";
            }
            file << std::endl;
        }
        file.close();
    }
}

void Chunk::loadFromPacket(sf::Packet& packet)
{
    // packet >> mPos.x >> mPos.y;   has already been read by the manager

    sf::Vector2i p;
    for (p.x = 0; p.x < getChunkSizeTile().x; p.x++)
    {
        for (p.y = 0; p.y < getChunkSizeTile().y; p.y++)
        {
            for (int k = 0; k < 3; k++)
            {
                unsigned int id;
                packet >> id;
                setId(p,k,id);
            }
        }
    }
}

void Chunk::writeToPacket(sf::Packet& packet)
{
    packet << mPos.x << mPos.y;

    sf::Vector2i p;
    for (p.x = 0; p.x < getChunkSizeTile().x; p.x++)
    {
        for (p.y = 0; p.y < getChunkSizeTile().y; p.y++)
        {
            for (int k = 0; k < 3; k++)
            {
                packet << getId(p,k);
            }
        }
    }
}

void Chunk::setId(sf::Vector2i tPos, unsigned int layer, unsigned int id)
{
    if (layer >= 0 && layer < mLayers.size() && tPos.x >= 0 && tPos.x < getChunkSizeTile().x && tPos.y >= 0 && tPos.y < getChunkSizeTile().y)
    {
        sf::Vector2f texCoords = idToTexCoords(id);
        sf::Vertex* quad = &mLayers[layer][(tPos.x + tPos.y * getChunkSizeTile().x) * 4];

        quad[0].position = sf::Vector2f(tPos.x * getTileSize().x, tPos.y * getTileSize().y);
        quad[1].position = sf::Vector2f((tPos.x + 1) * getTileSize().x, tPos.y * getTileSize().y);
        quad[2].position = sf::Vector2f((tPos.x + 1) * getTileSize().x, (tPos.y + 1) * getTileSize().y);
        quad[3].position = sf::Vector2f(tPos.x * getTileSize().x, (tPos.y + 1) * getTileSize().y);

        quad[0].texCoords = sf::Vector2f(texCoords.x, texCoords.y);
        quad[1].texCoords = sf::Vector2f(texCoords.x + getTileSize().x, texCoords.y);
        quad[2].texCoords = sf::Vector2f(texCoords.x + getTileSize().x, texCoords.y + getTileSize().y);
        quad[3].texCoords = sf::Vector2f(texCoords.x, texCoords.y + getTileSize().y);
    }
}

unsigned int Chunk::getId(sf::Vector2i tPos, unsigned int layer)
{
    if (layer >= 0 && layer < mLayers.size() && tPos.x >= 0 && tPos.x < getChunkSizeTile().x && tPos.y >= 0 && tPos.y < getChunkSizeTile().y)
    {
        sf::Vertex* quad = &mLayers[layer][(tPos.x + tPos.y * getChunkSizeTile().x) * 4];
        return texCoordsToId(quad[0].texCoords);
    }
    return 0;
}

void Chunk::draw(sf::RenderTarget& target, sf::FloatRect const& rect, unsigned int layer) const
{
    if (rect.intersects(getGlobalBounds()) && layer >= 0 && layer < 3)
    {
        target.draw(mLayers.at(layer),mStates);
    }
}

sf::Vector2i Chunk::getPos() const
{
    return mPos;
}

sf::FloatRect Chunk::getGlobalBounds() const
{
    return sf::FloatRect(sf::Vector2f(getChunkSize().x * mPos.x,getChunkSize().y * mPos.y), static_cast<sf::Vector2f>(getChunkSize()));
}

sf::Vector2i Chunk::getTileSize()
{
    return sf::Vector2i(32,32);
}

sf::Vector2i Chunk::getChunkSize()
{
    return sf::Vector2i(getTileSize().x * getChunkSizeTile().x, getTileSize().y * getChunkSizeTile().y);
}

sf::Vector2i Chunk::getChunkSizeTile()
{
    return sf::Vector2i(32,32);
}

sf::Time Chunk::getReleaseTime()
{
    return sf::seconds(30);
}

std::string Chunk::getFilenameFromPos(sf::Vector2i pos)
{
    return "Assets/World/" + ah::to_string(pos.x) + "_" + ah::to_string(pos.y) + ".chunk";
}

unsigned int Chunk::texCoordsToId(sf::Vector2f texCoords)
{
    return getTilesPerLine() * (texCoords.y / getTileSize().y) + texCoords.x / getTileSize().x;
}

sf::Vector2f Chunk::idToTexCoords(unsigned int id)
{
    return sf::Vector2f((id % getTilesPerLine()) * getTileSize().x, (id / getTilesPerLine()) * getTileSize().y);
}

unsigned int Chunk::getTilesPerLine()
{
    return mTextureSize.x / getTileSize().x;
}

std::vector<unsigned int> Chunk::initializeCollisions()
{
    std::vector<unsigned int> collisions;
    //collisions.push_back();
    return collisions;
}

bool Chunk::isCollide(unsigned int id)
{
    for (unsigned int i = 0; i < mCollisionIds.size(); i++)
    {
        if (id == mCollisionIds[i])
        {
            return true;
        }
    }
    return false;
}
