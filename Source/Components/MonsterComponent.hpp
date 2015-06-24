#ifndef MONSTERCOMPONENT_HPP
#define MONSTERCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

class MonsterComponent : public es::Component
{
    public:
        enum Type
        {
            Bat,
            Bee,
            // TODO (#7#): Add Monsters
        };

        MonsterComponent(Type type = Type::Bat);

        static std::string getId();

        static sf::Vector2f getSize(Type type);
        static std::string getTextureId(Type type);
        static sf::Vector2i getSheetSize(Type type);
        static sf::FloatRect getCollisionBox(Type type);
        static float getSpeed(Type type);
        static unsigned int getLife(Type type);
        static float getViewDistance(Type type);
        static float getOutOfView(Type type);
        static float getRange(Type type);
        static unsigned int getDamage(Type type);
        static sf::Time getCooldown(Type type);

        static void loadMonsterTextures();
        static void releaseMonsterTextures();

    private:
        Type mType;
};

#endif // MONSTERCOMPONENT_HPP
