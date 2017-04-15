#include "server.h"
#include "client.h"


Server::Server(boost::asio::io_service& io_service, unsigned short port)
    : QObject{}
    , acceptor{io_service, {boost::asio::ip::address_v4::any(), port}}
    , socket{io_service}
{
    acceptor.async_accept(socket, std::bind(&Server::accept, this, std::placeholders::_1));
}

void Server::stop()
{
}

void Server::accept(const boost::system::error_code& ec)
{
    if (ec)
    {
        emit error(make_error(ec));
    }
    else
    {
        auto client = std::make_shared<Client>(std::move(socket));
        connect(client.get(), &Client::disconnected, [this, &client]{ remove_client(client); });
        clients.emplace_back(client);
        emit info(tr("New client came"));
        client->start();
    }
}

QString Server::make_error(const boost::system::error_code& ec) const
{
    return tr("Error happened: %1. Code: %2").arg(QString::fromStdString(ec.message())).arg(ec.value());
}

void Server::remove_client(const std::shared_ptr<Client>& client)
{
    clients.erase(std::find(clients.begin(), clients.end(), client));
    emit info("Client disconnected");
}
