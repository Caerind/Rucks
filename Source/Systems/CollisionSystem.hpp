#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"
#include "../Components.hpp"
#include <SFML/System/Vector2.hpp>

#include "../Map/Map.hpp"
#include "../Map/Orthogonal.hpp"
#include "../Map/DefaultGen.hpp"

#include "../../Aharos/Helper/CollisionShape.hpp"

class CollisionSystem : public es::System
{
    public:
        typedef map::Map<map::Orthogonal,map::DefaultGen<map::Orthogonal>> WorldMap;

        CollisionSystem(WorldMap& map);

        static std::string getId();

        bool handle(es::Entity::Ptr e, sf::Vector2f& movement);
        bool projectileCollision(sf::FloatRect const& rect, es::Entity::Ptr& e);

    private:
        WorldMap& mMap;
};

#endif // COLLISIONSYSTEM_HPP
