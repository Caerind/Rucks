#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "LifeComponent.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIComponent : public es::Component
{
    public:
        AIComponent();

        static std::string getId();
        static es::ComponentFilter getTargetFilter();

        void setTarget(es::Entity::Ptr target);
        es::Entity::Ptr getTarget();
        bool hasTarget();

        void setMonster(bool monster);
        bool isMonster() const;

        void setViewDistance(float distance);
        float getViewDistance() const;

        void setOutOfView(float distance);
        float getOutOfView() const;

    private:
        es::Entity::Ptr mTarget;
        bool mIsMonster;
        float mViewDistance;
        float mOutOfView;
};

#endif // AICOMPONENT_HPP
