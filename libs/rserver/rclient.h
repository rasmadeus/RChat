#ifndef RCLIENT_H
#define RCLIENT_H

class QTcpSocket;
#include <QAbstractSocket>
#include <QObject>

class RClient : public QObject
{
    Q_OBJECT
public:
    explicit RClient(QObject* parent = 0);
    explicit RClient(QTcpSocket* client, QObject* parent = 0);
    const QString& getNickName() const;
    void connectToHost(const QString& address, quint16 port);
    void sayToHost(const QString& msg);
public slots:
    void disconnectFromHost();
signals:
    void disconnectedFromHost();
    void errorHappened(QAbstractSocket::SocketError);
    void msgCame(const QString& value);
private:
    void makeDefaultNickName();
    void makeEvents();
    QTcpSocket* client;
    QString nickName;

};

#endif // RCLIENT_H
