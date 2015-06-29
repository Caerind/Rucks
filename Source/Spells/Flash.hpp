#ifndef FLASH_HPP
#define FLASH_HPP

#include "Spell.hpp"

class Flash : public Spell
{
    public:
        Flash();

        virtual void activate();
};

#endif // FLASH_HPP
