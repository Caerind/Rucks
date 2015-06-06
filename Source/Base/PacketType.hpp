#ifndef PACKETTYPE_HPP_INCLUDED
#define PACKETTYPE_HPP_INCLUDED

namespace Server2Client
{
    enum Type
    {
        None = 0,
        ClientJoined,
        ClientLeft,
        ServerStopped,
        Message,
        //
        SendChunk,
        ModifyChunk,
        //
        ObjectAddition,
        ObjectDeletion,
        ObjectUpdate,
    };
}

namespace Client2Server
{
    enum Type
    {
        None = 0,
        Login,
        Disconnect,
        Message,
        //
        AskChunk,
        ModifyChunk,
        //
        PlayerUpdate,
        SendAttack,
    };
}

#endif // PACKETTYPE_HPP_INCLUDED
