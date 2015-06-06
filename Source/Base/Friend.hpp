#ifndef FRIEND_HPP
#define FRIEND_HPP

#include <string>

class Friend
{
    public:
        Friend();

        void setUsername(std::string const& username);
        std::string getUsername() const;

        void setClientId(unsigned int id);
        unsigned int getClientId() const;

        void setPlayerId(unsigned int id);
        unsigned int getPlayerId() const;

    private:
        std::string mUsername;
        unsigned int mClientId;
        unsigned int mPlayerId;
};

#endif // FRIEND_HPP
