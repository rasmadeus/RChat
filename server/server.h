#ifndef SERVER_H
#define SERVER_H

#include "room.h"
#include "session.h"

using boost::asio::ip::tcp;


class Server
{
public:
    Server(boost::asio::io_context& ioContext, unsigned short port);

private:
    void accept();

private:
    tcp::acceptor _acceptor;
    Room _room;
};


#endif // SERVER_H
