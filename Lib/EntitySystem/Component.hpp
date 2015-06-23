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
};

typedef std::map<std::string,Component*> ComponentArray;
typedef std::vector<std::string> ComponentFilter;

}

#endif // ES_COMPONENT_HPP
