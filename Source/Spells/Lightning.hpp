#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include "Spell.hpp"

class Lightning : public Spell
{
    public:
        Lightning();

        virtual void activate();
};

#endif // LIGHTNING_HPP
