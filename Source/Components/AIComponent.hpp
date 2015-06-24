#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "LifeComponent.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIComponent : public es::Component
{
    public:
        enum Type
        {
            Fighter = 0,
            Pacific,
        };

        AIComponent(float view = 100.f, float out = 200.f, Type type = Type::Fighter);

        static std::string getId();
        static es::ComponentFilter getTargetFilter();

        void setType(Type type);
        Type getType() const;
        bool isFighter() const;
        bool isPacific() const;

        void setTarget(es::Entity::Ptr target);
        es::Entity::Ptr getTarget();
        bool hasTarget();

        void setViewDistance(float distance);
        float getViewDistance() const;

        void setOutOfView(float distance);
        float getOutOfView() const;

        void resetBoredTime();
        sf::Time getBoredTime() const;

    private:
        Type mType;
        es::Entity::Ptr mTarget;
        float mViewDistance;
        float mOutOfView;
        sf::Clock mBoredTime;
};

#endif // AICOMPONENT_HPP
