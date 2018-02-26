#ifndef SESSION_H
#define SESSION_H

#include "message.h"

class Room;

using boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(Room& room, tcp::socket&& socket);
    void start();
    void write(const Message& msg);

private:
    void read();

private:
    Room& _room;
    tcp::socket _socket;
    Message _msg;
};

#endif // SESSION_H
