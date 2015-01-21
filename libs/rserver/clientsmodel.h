#ifndef CLIENTSMODEL_H
#define CLIENTSMODEL_H

class Clients;
#include <QAbstractListModel>

class ClientsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ClientsModel(Clients* clients, QObject* parent = 0);
    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
public slots:
    void removeOne(const QModelIndex& index);
private slots:
    void reset();
private:
    Clients* clients;
};

#endif // CLIENTSMODEL_H
