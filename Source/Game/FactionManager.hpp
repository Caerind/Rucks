#ifndef FACTIONMANAGER_HPP
#define FACTIONMANAGER_HPP

#include <map>
#include <fstream>

#include "Faction.hpp"

class FactionManager
{
    public:
        FactionManager();

        void loadFromFile(std::string const& filename);
        void saveToFile(std::string const& filename);

        void create(int id);
        void remove(int id);
        Faction& get(int id);

        std::size_t getMemberCount(int id);
        void addMember(int id);
        void removeMember(int id);

        bool isAlly(int id1, int id2);
        bool isEnemy(int id1, int id2);
        bool isNeutral(int id1, int id2);

    private:
        std::map<int,Faction> mFactions;
};

#endif // FACTIONMANAGER_HPP
