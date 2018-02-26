#ifndef ROOM_H
#define ROOM_H

#include "message.h"

class Session;


class Room
{
public:
    void join(const std::shared_ptr<Session>& session);
    void leave(const std::shared_ptr<Session>& session);
    void say(const Message& msg);

private:
    std::set<std::shared_ptr<Session>> _sessions;
};

#endif // ROOM_H
