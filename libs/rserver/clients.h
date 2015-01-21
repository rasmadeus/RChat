#ifndef CLIENTS_H
#define CLIENTS_H

class QTcpSocket;
class RClient;
#include <QObject>

class Clients : public QObject
{
    Q_OBJECT
public:
    explicit Clients(QObject* parent = 0);
    ~Clients();
    RClient* add(QTcpSocket* newClient);
    void clear();
    int count() const;
    QString getClientName(int i) const;
    void sayAll(const QString& msg);
    void disconnectAll();
    void disconnectOne(int i);
signals:
    void clientDisconnected();
    void newClientWasAdded();
private slots:
    void removeDisconnectedClient();
private:
    QList<RClient*> clients;
};

#endif // CLIENTS_H
