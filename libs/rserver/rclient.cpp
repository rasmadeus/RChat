#include "rclient.h"

#include <QTcpSocket>
RClient::RClient(QObject* parent) :
    QObject(parent)
{
    client = new QTcpSocket(this);
    makeDefaultNickName();
    makeEvents();
}

RClient::RClient(QTcpSocket* client, QObject* parent) :
    QObject(parent)
{
    this->client = client;
    makeDefaultNickName();
    makeEvents();
}


#include <QHostAddress>
void RClient::makeDefaultNickName()
{
    const QString clientAddress = client->peerAddress().toString();
    const quint16 clientPort = client->peerPort();
    nickName = QString("<%1:%2>").arg(clientAddress).arg(clientPort);
}

void RClient::connectToHost(const QString& address, quint16 port)
{
    client->close();
    client->connectToHost(address, port);
    client->waitForConnected();
}

void RClient::disconnectFromHost()
{
    client->close();
}
#include <QDebug>
void RClient::sayToHost(const QString& msg)
{
 //   if(client->isOpen()){
        client->write(msg.toUtf8());
        client->flush();
        client->waitForBytesWritten();
 //   }
}

void RClient::makeEvents()
{
    connect(
        client,
        SIGNAL(disconnected()),
        SIGNAL(disconnectedFromHost())
    );
    connect(
        client,
        SIGNAL(error(QAbstractSocket::SocketError)),
        SIGNAL(errorHappened(QAbstractSocket::SocketError))
    );
    connect(
        client,
        &QTcpSocket::readyRead,
        [this](){ emit msgCame(QString(client->readAll())); }
    );
}

const QString& RClient::getNickName() const
{
    return nickName;
}
