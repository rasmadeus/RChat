#ifndef SERVER_H
#define SERVER_H

class Client;


class Server : public QObject
{
    Q_OBJECT

public:
    Server(boost::asio::io_service& io_service, unsigned short port);
    void stop();

signals:
    void error(const QString& msg);
    void info(const QString& msg);

private:
    void accept(const boost::system::error_code& ec);
    QString make_error(const boost::system::error_code& ec) const;
    void remove_client(const std::shared_ptr<Client>& client);

private:
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
    std::vector<std::shared_ptr<Client>> clients;
};

#endif // SERVER_H
