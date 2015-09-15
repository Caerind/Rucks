#ifndef FACTIONCOMPONENT_HPP
#define FACTIONCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../../Aharos/EntitySystem/ComponentFilter.hpp"
#include "../../Aharos/EntitySystem/EntityManager.hpp"

#include "../Game/Faction.hpp"
#include "../World.hpp"
#include "../Components.hpp"

class FactionComponent : public es::Component
{
    public:
        FactionComponent();

        static std::string getId();

        void setFactionId(int factionId);
        int getFactionId() const;

        Faction getFaction();

        es::EntityArray getListOfEnemies();

    private:
        int mFactionId;
};

#endif // FACTIONCOMPONENT_HPP
