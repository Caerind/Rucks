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

        static std::string getTextureId(Type type);

        static void loadMonsterTextures();
        static void releaseMonsterTextures();

    private:
        Type mType;
};

#endif // MONSTERCOMPONENT_HPP
