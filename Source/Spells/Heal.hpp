#ifndef HEAL_HPP
#define HEAL_HPP

#include "Spell.hpp"

class Heal : public Spell
{
    public:
        Heal();

        virtual void activate();
        virtual bool canSpell();
};

#endif // HEAL_HPP
