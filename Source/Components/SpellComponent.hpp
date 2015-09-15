#ifndef SPELLCOMPONENT_HPP
#define SPELLCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"

#include "../../Aharos/Renderer/Renderer.hpp"
#include "../../Aharos/Renderer/Sprite.hpp"

#include "TransformComponent.hpp"

#include "../Spells.hpp"

#include <array>

class SpellComponent : public es::Component, public rd::Sprite
{
    public:
        SpellComponent();
        ~SpellComponent();

        static std::string getId();

        Spell* getSpell(std::size_t i);
        void setSpell(std::size_t i, Spell* spell);

        bool isCasting() const;
        sf::Time getCasting() const;
        Spell* getActiveSpell();

        bool canSpell(std::size_t i);
        void spell(std::size_t i);

        void update(sf::Time dt);
        void render(sf::RenderTarget& target);

        void setSpellPosition(float x, float y);

    private:
        std::array<Spell*,5> mSpells;

        std::size_t mCastingSpell;
        sf::Time mCasting;
        bool mIsCasting;

        sf::Vector2f mPosition;
};

#endif // SPELLCOMPONENT_HPP
