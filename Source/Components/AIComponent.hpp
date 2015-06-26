#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"

// Target Filter
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "LifeComponent.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIComponent : public es::Component
{
    public:
        AIComponent();

        static std::string getId();

        void setTarget(es::Entity::Ptr target);
        es::Entity::Ptr getTarget();
        bool hasTarget();

        void setViewDistance(float distance);
        float getViewDistance() const;

        void setOutOfView(float distance);
        float getOutOfView() const;

    private:
        es::Entity::Ptr mTarget;
        float mViewDistance;
        float mOutOfView;
};

#endif // AICOMPONENT_HPP
