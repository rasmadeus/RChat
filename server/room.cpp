#include "room.h"

#include "session.h"


void Room::join(const std::shared_ptr<Session>& session)
{
    _sessions.insert(session);
}

void Room::leave(const std::shared_ptr<Session>& session)
{
    _sessions.erase(session);
}

void Room::say(const Message& msg)
{
    for(auto& session : _sessions)
        session->write(msg);
}
