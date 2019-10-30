#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include "consolereader.h"

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr, QString str = "127.0.0.1", quint16 port = 6000);

signals:

public slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer(QString data);
    void slotConnected();


private:
    QTcpSocket *mTcpSocket;
    ConsoleReader *consoleReader;
};

#endif // MYTCPSOCKET_H
