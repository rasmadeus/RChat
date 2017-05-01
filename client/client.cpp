#include "client.h"


Client::Client(boost::asio::io_service& io_service)
    : QObject{}
    , io_service(io_service)
    , socket(io_service)
{
}

void Client::write(const chat_message& msg)
{
    boost::asio::async_write(socket, boost::asio::buffer(msg.data(), msg.length()), [this](boost::system::error_code ec, std::size_t length){
        if (!ec)
            emit info("Message was sent");
    });
}

void Client::open(const std::string& host, const std::string& port)
{
    emit info(tr("Try to open socket"));
    boost::asio::ip::tcp::resolver resolver{io_service};
    do_connect(resolver.resolve({host, port}));
}

void Client::close()
{
    emit info(tr("Try to close socket"));
    io_service.post([this]{
        socket.close();
        emit info("Socket about to be closed");
    });
}


void Client::do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
    boost::asio::async_connect(socket, endpoint_iterator, [this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator){
        if (!ec)
        {
            emit info(tr("Connected to server"));
            do_read_header();
        }
    });
}

void Client::do_read_header()
{
    boost::asio::async_read(socket, boost::asio::buffer(read_msg.data(), chat_message::header_length), [this](boost::system::error_code ec, std::size_t length){
        if (!ec && read_msg.decode_header())
            do_read_body();
        else
        {
            socket.close();
            emit info("Socket about to be closed");
        }
    });
}

void Client::do_read_body()
{
    boost::asio::async_read(socket, boost::asio::buffer(read_msg.body(), read_msg.body_length()), [this](boost::system::error_code ec, std::size_t length){
        if (!ec)
        {
            emit info(tr("Message came: %1").arg(QString::fromStdString(std::string{read_msg.body()})));
            do_read_header();
        }
        else
        {
            emit info(tr("Error"));
            socket.close();
        }
    });
}
