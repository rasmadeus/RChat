#include "clients.h"

Clients::Clients(QObject *parent) :
    QObject(parent)
{
}

Clients::~Clients()
{
    clear();
}

#include "rclient.h"
RClient *Clients::add(QTcpSocket* newClient)
{
    RClient* client = new RClient(newClient, this);
    clients.push_back(client);
    connect(client, SIGNAL(disconnectedFromHost()), SIGNAL(clientDisconnected()));
    connect(client, SIGNAL(disconnectedFromHost()), SLOT(removeDisconnectedClient()));
    emit newClientWasAdded();
    return client;
}

void Clients::removeDisconnectedClient()
{
    RClient* client = qobject_cast<RClient*>(sender());
    clients.removeOne(client);
    delete client;
}

int Clients::count() const
{
    return clients.size();
}

#include <QHostAddress>
QString Clients::getClientName(int i) const
{
    return clients.at(i)->getNickName();
}

void Clients::clear()
{
    qDeleteAll(clients);
    clients.clear();
}

void Clients::sayAll(const QString& msg)
{
    foreach(RClient* client, clients){
       client->sayToHost(msg);
    }
}

void Clients::disconnectAll()
{
    foreach(RClient* client, clients) {
        client->disconnectFromHost();
    }
}

void Clients::disconnectOne(int i)
{
    clients.at(i)->disconnectFromHost();
}
