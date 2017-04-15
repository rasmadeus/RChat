#ifndef CLIENT_H
#define CLIENT_H


class Client : public QObject
{
    Q_OBJECT

public:
    Client(boost::asio::ip::tcp::socket&& socket);
    void start();

signals:
    void disconnected();

private:
    boost::asio::ip::tcp::socket socket;
};

#endif // CLIENT_H
