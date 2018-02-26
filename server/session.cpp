#include "room.h"
#include "session.h"


Session::Session(Room& room, tcp::socket&& socket)
    : _room{ room }
    , _socket{ std::move(socket) }
{
}

void Session::start()
{
    read();
}

void Session::write(const Message& msg)
{
    auto self{ shared_from_this() };
    boost::asio::async_write(
        _socket,
        boost::asio::buffer(msg.data(), msg.size()),
        [this, self](const boost::system::error_code& ec, std::size_t length)
        {
            std::ignore = length;

            if (ec)
            {
                _room.leave(shared_from_this());
            }
            else
            {
                read();
            }
        }
    );
}

void Session::read()
{
    auto self{ shared_from_this() };
    _socket.async_read_some(
        boost::asio::buffer(_msg.data(), _msg.size()),
        [this, self](const boost::system::error_code& ec, std::size_t length)
        {
            std::ignore = length;

            if (ec)
            {
                _room.leave(shared_from_this());
            }
            else
            {
                _room.say(_msg);
            }
        }
    );
}
