#ifndef HUMANSYSTEM_HPP
#define HUMANSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"

#include "../Components.hpp"

#include <cassert>
#include <SFML/System/Time.hpp>

#include "../Components/WeaponComponent.hpp"
#include "../Components/SpellComponent.hpp"

class HumanSystem : public es::System
{
    public:
        HumanSystem();

        static std::string getId();

        void update();

        void handleWeaponOnMoving(WeaponComponent& w, sf::Vector2i sPos);
        void handleWeaponOnAttack(WeaponComponent& w, int dir);
        void handleSpell(SpellComponent& s, int dir, es::Entity::Ptr e);
};

#endif // HUMANSYSTEM_HPP
