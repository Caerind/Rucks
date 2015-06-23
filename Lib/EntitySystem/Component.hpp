#ifndef ES_COMPONENT_HPP
#define ES_COMPONENT_HPP

#include <map>
#include <string>
#include <vector>

namespace es
{

class Component
{
    public:
        Component();
        virtual ~Component();

        static std::string getId();

        void setIdAttachedTo(std::size_t id);
        std::size_t getIdAttachedTo() const;

    private:
        std::size_t mIdAttachedTo;
};

typedef std::map<std::string,Component*> ComponentArray;
typedef std::vector<std::string> ComponentFilter;

}

#endif // ES_COMPONENT_HPP
