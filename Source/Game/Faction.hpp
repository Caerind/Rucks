#ifndef FACTION_HPP
#define FACTION_HPP

#include <vector>
#include <string>

class Faction
{
    public:
        Faction();

        void setId(int id);
        int getId() const;

        void setName(std::string const& name);
        std::string getName() const;

        bool isAlly(int id) const;
        bool isEnemy(int id) const;
        bool isNeutral(int id) const;

        void addAlly(int id);
        void addEnemy(int id);
        void removeAlly(int id);
        void removeEnemy(int id);

        std::size_t getMemberCount() const;
        void addMember();
        void removeMember();

    private:
        int mFactionId;
        std::string mName;
        std::vector<int> mAllies;
        std::vector<int> mEnemies;
        std::size_t mMemberCount;
};

#endif // FACTION_HPP
