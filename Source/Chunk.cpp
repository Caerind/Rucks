#include "Chunk.hpp"
#include "World.hpp"

Chunk::Chunk(World& world) : mWorld(world), mTexture(world.getApplication().getTexture("Assets/Textures/tileset.png"))
{
    mPos = sf::Vector2i(-9999,-9999);

    for (unsigned int i = 0; i < mLayers.size(); i++)
    {
        mLayers[i].resize(getChunkSizeTile() * getChunkSizeTile() * 4);
        mLayers[i].setPrimitiveType(sf::Quads);
    }
}

Chunk::~Chunk()
{
    if (!mWorld.isOnline())
    {
        saveToFile();
    }
}

void Chunk::load(sf::Vector2i pos)
{
    if (!mWorld.isOnline())
    {
        if (mPos != sf::Vector2i(-9999,-9999))
        {
            saveToFile();
        }
        setPos(pos);
        if (!loadFromFile())
        {
            generate();
        }
    }
}

void Chunk::loadFromPacket(sf::Packet& packet)
{
    // packet >> mPos.x >> mPos.y;   has already been read by the manager

    sf::Vector2i p;
    for (p.x = 0; p.x < (int)getChunkSizeTile(); p.x++)
    {
        for (p.y = 0; p.y < (int)getChunkSizeTile(); p.y++)
        {
            for (int k = 0; k < 3; k++)
            {
                unsigned int id;
                packet >> id;
                setTileId(p,k,id);
            }
        }
    }
}

void Chunk::loadInPacket(sf::Packet& packet)
{
    packet << mPos.x << mPos.y;

    sf::Vector2i p;
    for (p.x = 0; p.x < (int)getChunkSizeTile(); p.x++)
    {
        for (p.y = 0; p.y < (int)getChunkSizeTile(); p.y++)
        {
            for (int k = 0; k < 3; k++)
            {
                packet << getTileId(p,k);
            }
        }
    }
}

void Chunk::setPos(sf::Vector2i pos)
{
    mPos = pos;
    setPosition(mPos.x * (float)Chunk::getChunkSizePx(), mPos.y * (float)Chunk::getChunkSizePx());
}

sf::Vector2i Chunk::getPos() const
{
    return mPos;
}

void Chunk::setTileId(sf::Vector2i tilePos, unsigned int layer, unsigned int id)
{
    if (layer >= 0 && layer < mLayers.size() && tilePos.x >= 0 && tilePos.x < (int)getChunkSizeTile() && tilePos.y >= 0 && tilePos.y < (int)getChunkSizeTile())
    {
        sf::Vector2f texCoords = idToTexCoords(id);
        sf::Vertex* quad = &mLayers[layer][(tilePos.x + tilePos.y * getChunkSizeTile()) * 4];

        quad[0].position = sf::Vector2f(tilePos.x * getTileSize(), tilePos.y * getTileSize());
        quad[1].position = sf::Vector2f((tilePos.x + 1) * getTileSize(), tilePos.y * getTileSize());
        quad[2].position = sf::Vector2f((tilePos.x + 1) * getTileSize(), (tilePos.y + 1) * getTileSize());
        quad[3].position = sf::Vector2f(tilePos.x * getTileSize(), (tilePos.y + 1) * getTileSize());

        quad[0].texCoords = sf::Vector2f(texCoords.x, texCoords.y);
        quad[1].texCoords = sf::Vector2f(texCoords.x + getTileSize(), texCoords.y);
        quad[2].texCoords = sf::Vector2f(texCoords.x + getTileSize(), texCoords.y + getTileSize());
        quad[3].texCoords = sf::Vector2f(texCoords.x, texCoords.y + getTileSize());
    }
}

unsigned int Chunk::getTileId(sf::Vector2i tilePos, unsigned int layer)
{
    if (layer >= 0 && layer < mLayers.size() && tilePos.x >= 0 && tilePos.x < (int)getChunkSizeTile() && tilePos.y >= 0 && tilePos.y < (int)getChunkSizeTile())
    {
        sf::Vertex* quad = &mLayers[layer][(tilePos.x + tilePos.y * getChunkSizeTile()) * 4];
        return texCoordsToId(quad[0].texCoords);
    }
    return 0;
}

void Chunk::render(sf::RenderTarget& target, unsigned int layer) const
{
    if (layer >= 0 && layer < mLayers.size())
    {
        sf::RenderStates states;
        states.transform *= getTransform();
        states.texture = &mTexture;
        target.draw(mLayers[layer],states);
    }
}

sf::FloatRect Chunk::getGlobalBounds() const
{
    return sf::FloatRect(getPosition().x, getPosition().y, getChunkSizePx(), getChunkSizePx());
}

unsigned int Chunk::getChunkSizePx()
{
    return 1024;
}

unsigned int Chunk::getChunkSizeTile()
{
    return 32;
}

unsigned int Chunk::getTileSize()
{
    return 32;
}

bool Chunk::loadFromFile()
{
    std::ifstream file("Save/" + posToStr() + ".chunk");
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
                    setTileId(pos,l,id);
                l++;
            }
            pos.x++;
        }
        pos.y++;
    }
    file.close();
    return true;
}

void Chunk::saveToFile()
{
    std::ofstream file("Save/" + posToStr() + ".chunk");
    sf::Vector2i pos;
    for (pos.y = 0; pos.y < (int)getChunkSizeTile(); pos.y++)
    {
        for (pos.x = 0; pos.x < (int)getChunkSizeTile(); pos.x++)
        {
            file << getTileId(pos,0) << "-";
            file << getTileId(pos,1) << "-";
            file << getTileId(pos,2) << ";";
        }
        file << std::endl;
    }
    file.close();
}

void Chunk::generate()
{
    for (unsigned int i = 0; i < getChunkSizeTile(); i++)
    {
        for (unsigned int j = 0; j < getChunkSizeTile(); j++)
        {
            setTileId(sf::Vector2i(i,j),0,thor::random(0,10));
        }
    }
    saveToFile();
}

std::string Chunk::posToStr()
{
    std::ostringstream oss;
    oss << mPos.x << "_" << mPos.y;
    return oss.str();
}

unsigned int Chunk::texCoordsToId(sf::Vector2f texCoords)
{
    return getTilesPerLine() * (texCoords.y / getTileSize()) + texCoords.x / getTileSize();
}

sf::Vector2f Chunk::idToTexCoords(unsigned int id)
{
    return sf::Vector2f((id % getTilesPerLine()) * getTileSize(), (id / getTilesPerLine()) * getTileSize());
}

unsigned int Chunk::getTilesPerLine()
{
    return mTexture.getSize().x / getTileSize();
}
