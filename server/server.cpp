#include "server.h"


Server::Server(boost::asio::io_context& ioContext, unsigned short port)
    : _acceptor{ ioContext, tcp::endpoint{ tcp::v4(), port } }
{
    accept();
}

void Server::accept()
{
    _acceptor.async_accept(
        [this](const boost::system::error_code& ec, tcp::socket&& socket)
        {
            if (!ec)
            {
                auto session = std::make_shared<Session>(_room, std::move(socket));
                _room.join(session);
                session->start();
            }
            accept();
        }
    );
}
