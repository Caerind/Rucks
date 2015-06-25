#ifndef PROJECTILECOMPONENT_HPP
#define PROJECTILECOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class ProjectileComponent : public es::Component
{
    public:
        enum Type
        {
            None,
            Arrow,
            // TODO (#7#): More Projectiles !
        };

        ProjectileComponent(Type type);

        static std::string getId();

        void setType(Type type);
        Type getType() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(unsigned int damage);
        unsigned int getDamage() const;

        void setSpeed(float speed);
        float getSpeed() const;

        void setDirection(sf::Vector2f const& direction);
        sf::Vector2f getDirection() const;

        void addDistanceTraveled(float distance);
        void addDistanceTraveled(sf::Vector2f const& movement);
        float getDistanceTraveled() const;
        bool fallDown() const;

        static std::string getTextureId(Type type);
        static sf::Vector2f getSize(Type type);
        static sf::Vector2i getSheetSize(Type type);
        static sf::IntRect getTextureRect(Type type);

        static void loadProjectileTextures();
        static void releaseProjectileTextures();

    private:
        Type mType;
        float mRange;
        unsigned int mDamage;
        float mSpeed;
        sf::Vector2f mDirection;

        float mDistanceTraveled;
};

#endif // PROJECTILECOMPONENT_HPP
