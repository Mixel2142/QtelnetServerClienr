#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>

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
signals:
    void text(QByteArray data);
private:
    QTcpServer *mTcpServer;
};

#endif // MYTCPSERVER_H
