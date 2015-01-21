#include "rserver.h"

#include "clients.h"
#include <QTcpServer>
RServer::RServer(QObject* parent) :
    QObject(parent)
{
    port = 9998;
    server = new QTcpServer(parent);
    connect(server, SIGNAL(newConnection()), SLOT(newClientBound()));
    clients = new Clients(this);
}

RServer::~RServer()
{
    stop();
}

#include <QTcpSocket>
#include "rclient.h"
void RServer::newClientBound()
{
    QTcpSocket* newClient = server->nextPendingConnection();
    RClient* newRClient = clients->add(newClient);
    connect(
        newRClient,
        &RClient::disconnectedFromHost,
        [this, newRClient](){sayAll(newRClient->getNickName() + tr(" leave us."));}
    );
    connect(
        newRClient,
        &RClient::msgCame,
        [this, newRClient](const QString& msg){
            return sayAll(newRClient->getNickName() + msg);
        }
    );
}

void RServer::start()
{
    server->listen(QHostAddress::Any, port);
}

void RServer::stop()
{
    sayAll(tr("Server is about to close."));
    server->close();
    clients->clear();
}

void RServer::sayAll(const QString &msg)
{
    clients->sayAll(msg);
}

#include "clientsmodel.h"
ClientsModel* RServer::makeListModel(QObject* parent)
{
    return new ClientsModel(clients, parent);
}

quint16 RServer::getPort() const
{
    return port;
}

void RServer::setPort(quint16 value)
{
    port = value;
}

void RServer::disconnectAll()
{
    clients->sayAll(tr("You will be disconnected by server."));
    clients->disconnectAll();
}
