#ifndef RSERVER_H
#define RSERVER_H

class QTcpSocket;
class QTcpServer;
class Clients;
class RClient;
class ClientsModel;
#include <QObject>

class RServer : public QObject
{
    Q_OBJECT
public:
    explicit RServer(QObject* parent = 0);
    ~RServer();
    ClientsModel* makeListModel(QObject* parent);
    quint16 getPort() const;
public slots:
    void start();
    void stop();
    void setPort(quint16 value);
    void disconnectAll();
    void sayAll(const QString& msg);
private slots:
    void newClientBound();
private:
    QTcpServer* server;
    Clients* clients;
    quint16 port;
};

#endif // RSERVER_H
