#include "PlayerInputSystem.hpp"
#include "../Configuration.hpp"
#include "../World.hpp"

PlayerInputSystem::PlayerInputSystem()
: es::System()
, ah::ActionTarget(Configuration::instance().getPlayerInput())
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(PlayerInputComponent::getId());

    bind("up",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.y == 1.f || mMovement.y == 0.f)
            mMovement.y -= 1.f;
    });
    bind("left",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.x == 1.f || mMovement.x == 0.f)
            mMovement.x -= 1.f;
    });
    bind("down",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.y == -1.f || mMovement.y == 0.f)
            mMovement.y += 1.f;
    });
    bind("right",[&](ah::ActionTarget::Context context)
    {
        if (mMovement.x == -1.f || mMovement.x == 0.f)
            mMovement.x += 1.f;
    });
}

std::string PlayerInputSystem::getId()
{
    return "PlayerInputSystem";
}

void PlayerInputSystem::update(sf::Time dt)
{
    ah::ActionTarget::update();

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2f mvt = mMovement * dt.asSeconds() * mEntities[i]->getComponent<MovementComponent>().getSpeed();
        // TODO : Check Collisions
        mEntities[i]->getComponent<TransformComponent>().move(mvt);
    }

    if (mEntities.size() == 1)
    {
        World::instance().getView().setCenter(mEntities[0]->getComponent<TransformComponent>().getPosition());
    }

    mMovement = sf::Vector2f(0.f,0.f);
}
