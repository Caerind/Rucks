#ifndef HEAL_HPP
#define HEAL_HPP

#include "Spell.hpp"

class Heal : public Spell
{
    public:
        Heal();

        virtual void activate();
};

#endif // HEAL_HPP
