#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "Spell.hpp"

class Fireball : public Spell
{
    public:
        Fireball();

        virtual void activate();
};

#endif // FIREBALL_HPP
