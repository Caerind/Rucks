#ifndef FLASH_HPP
#define FLASH_HPP

#include "Spell.hpp"

class Flash : public Spell
{
    public:
        Flash();

        virtual void activate();
        virtual bool canSpell();
};

#endif // FLASH_HPP
