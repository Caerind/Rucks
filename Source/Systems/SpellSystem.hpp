#ifndef SPELLSYSTEM_HPP
#define SPELLSYSTEM_HPP

#include "../../Aharos/EntitySystem/System.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"
#include "../Components/SpellComponent.hpp"

class SpellSystem : public es::System
{
    public:
        SpellSystem();

        static std::string getId();

        void update(sf::Time dt);
};

#endif // SPELLSYSTEM_HPP
