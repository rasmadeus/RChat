#ifndef CLIENT_H
#define CLIENT_H


class Client : public QObject
{
    Q_OBJECT

public:

    Client(boost::asio::io_service& io_service);
    void connect(const std::string& server, const std::string& port);
    void disconnect();

signals:
    void connected();
    void disconnected();
    void info(const QString& msg);
    void error(const QString& msg);

private:
    void on_connect(const boost::system::error_code& ec, const boost::asio::ip::tcp::resolver::iterator& it);
    void do_disconnect();
    QString make_error(const boost::system::error_code& ec) const;

private:
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;
};

#endif // CLIENT_H
