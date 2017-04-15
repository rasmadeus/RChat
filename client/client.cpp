#include "client.h"

Client::Client(boost::asio::io_service& io_service)
    : QObject{}
    , io_service{io_service}
    , socket{io_service}
{
}

void Client::connect(const std::string& server, const std::string& port)
{
    emit info(tr("User request connect to [%1:%2]").arg(QString::fromStdString(server)).arg(QString::fromStdString(port)));
    const auto endpoint_it = boost::asio::ip::tcp::resolver{io_service}.resolve({server, port});
    boost::asio::async_connect(socket, endpoint_it, std::bind(&Client::on_connect, this, std::placeholders::_1, std::placeholders::_2));
}

void Client::disconnect()
{
    emit info(tr("User request disconnect"));
    io_service.post(std::bind(&Client::do_disconnect, this));
}

void Client::on_connect(const boost::system::error_code& ec, const boost::asio::ip::tcp::resolver::iterator& it)
{
    if (ec)
    {
        emit error(make_error(ec));
    }
    else
    {
        const auto endpoint = it->endpoint();
        const auto address = QString::fromStdString(endpoint.address().to_string());
        const unsigned short port = endpoint.port();
        emit info(tr("Succesfully connected to: [%1:%2]").arg(address).arg(port));
        emit connected();
    }
}

void Client::do_disconnect()
{
    boost::system::error_code shutdown_ec;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, shutdown_ec);
    if (shutdown_ec)
        emit error(make_error(shutdown_ec));
    socket.close();
    emit info(tr("Disconnected"));
    emit disconnected();
}

QString Client::make_error(const boost::system::error_code& ec) const
{
    return tr("Error happened: %1. Code: %2").arg(QString::fromStdString(ec.message())).arg(ec.value());
}
