#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QString str = "127.0.0.1", quint16 port = 6000);

signals:

public slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer(QString data);
    void slotConnected();


private:
    QTcpSocket *mTcpSocket;
};

#endif // MYTCPSOCKET_H
