#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"

// Target Filter
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "StatComponent.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

class AIComponent : public es::Component
{
    public:
        AIComponent();

        static std::string getId();

        bool setTargetId(std::size_t target);
        std::size_t getTargetId() const;
        es::Entity::Ptr getTarget();
        bool hasTarget();

        void setViewDistance(float distance);
        float getViewDistance() const;

        void setOutOfView(float distance);
        float getOutOfView() const;

    private:
        std::size_t mTarget;
        float mViewDistance;
        float mOutOfView;
};

#endif // AICOMPONENT_HPP
