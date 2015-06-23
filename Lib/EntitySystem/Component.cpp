#include "Component.hpp"

namespace es
{

Component::Component()
{
}

Component::~Component()
{
}

std::string Component::getId()
{
    return "Component";
}

void Component::setIdAttachedTo(std::size_t id)
{
    mIdAttachedTo = id;
}

std::size_t Component::getIdAttachedTo() const
{
    return mIdAttachedTo;
}

}
