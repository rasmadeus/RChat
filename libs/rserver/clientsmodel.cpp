#include "clientsmodel.h"

#include "clients.h"
ClientsModel::ClientsModel(Clients* clients, QObject *parent) :
    QAbstractListModel(parent)
{
    this->clients = clients;
    connect(clients, SIGNAL(clientDisconnected()), SLOT(reset()));
    connect(clients, SIGNAL(newClientWasAdded()), SLOT(reset()));
}

QVariant ClientsModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole){
        int row = index.row();
        QString clientName = clients->getClientName(row);
        return clientName;
    }
    return QVariant();
}

int ClientsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return clients->count();
}

Qt::ItemFlags ClientsModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ClientsModel::reset()
{
    beginResetModel();
    endResetModel();
}

void ClientsModel::removeOne(const QModelIndex& index)
{
    if (index.isValid()){
        beginResetModel();
        clients->disconnectOne(index.row());
        endResetModel();
    }
}
