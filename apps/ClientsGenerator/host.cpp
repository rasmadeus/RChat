#include "host.h"

Host::Host(QObject* parent) :
    QObject(parent),
    address("127.0.0.1"),
    port(9998)
{
}

void Host::setPort(int value)
{
    port = value;
}

void Host::setAddress(const QString& value)
{
    address = value;
}

#include <rclient.h>
void Host::generateClients(size_t count)
{
    for(size_t i = 0; i < count; ++i){
        RClient* client = new RClient(this);
        clients.push_back(client);
        connect(client, SIGNAL(msgCame(QString)), SIGNAL(newDataCame(QString)));
        client->connectToHost(address, port);
    }
}

#include <algorithm>
void Host::killAllClients()
{
    std::for_each(std::begin(clients), std::end(clients), [](RClient* client){client->disconnectFromHost();});
    qDeleteAll(clients);
    clients.clear();
}
