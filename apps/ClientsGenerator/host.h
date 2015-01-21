#ifndef HOST_H
#define HOST_H

class RClient;
#include <QObject>

class Host : public QObject
{
    Q_OBJECT
public:
    explicit Host(QObject* parent = 0);
public slots:
    void generateClients(size_t count);
    void killAllClients();
    void setPort(int value);
    void setAddress(const QString& value);
signals:
    void newDataCame(const QString& data);
private:
    QString address;
    quint16 port;
    QList<RClient*> clients;
};

#endif // HOST_H
