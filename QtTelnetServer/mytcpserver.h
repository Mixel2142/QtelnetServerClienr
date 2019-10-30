#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <myprocessbuilder.h>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
public slots:
    // for sockets
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();

private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
};

#endif // MYTCPSERVER_H
