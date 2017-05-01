#ifndef CLIENT_H
#define CLIENT_H

#include "message.h"


class Client : public QObject
{
    Q_OBJECT

public:
  Client(boost::asio::io_service& io_service);
  void write(const chat_message& msg);
  void open(const std::string& host, const std::string& port);
  void close();

signals:
    void info(const QString& msg);
    void error(const QString& msg);

private:
  void do_connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
  void do_read_header();
  void do_read_body();

private:
  boost::asio::io_service& io_service;
  boost::asio::ip::tcp::socket socket;
  chat_message read_msg;
};

#endif // CLIENT_H
