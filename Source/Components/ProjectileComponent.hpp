#ifndef PROJECTILECOMPONENT_HPP
#define PROJECTILECOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class ProjectileComponent : public es::Component
{
    public:
        enum Type
        {
            None,
            Arrow,
            Fireball,
            // TODO : More Projectiles !
        };

        ProjectileComponent();

        static std::string getId();

        void setStrickerId(std::size_t stricker);
        std::size_t getStrickerId() const;
        es::Entity::Ptr getStricker();

        void setType(Type type);
        Type getType() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(unsigned int damage);
        unsigned int getDamage() const;

        void setDirection(sf::Vector2f const& direction);
        sf::Vector2f getDirection() const;

        void addDistanceTraveled(float distance);
        void addDistanceTraveled(sf::Vector2f const& movement);
        float getDistanceTraveled() const;
        bool fallDown() const;

        /*static std::string getTextureId(Type type);
        static sf::Vector2f getSize(Type type);
        static sf::Vector2i getSheetSize(Type type);
        static sf::IntRect getTextureRect(Type type);*/

    private:
        Type mType;

        float mRange;
        unsigned int mDamage;
        sf::Vector2f mDirection;

        float mDistanceTraveled;

        std::size_t mStricker;
};

#endif // PROJECTILECOMPONENT_HPP
