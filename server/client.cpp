#include "client.h"

Client::Client(boost::asio::ip::tcp::socket&& socket)
    : QObject{}
    , socket{std::move(socket)}
{
}

void Client::start()
{
}
