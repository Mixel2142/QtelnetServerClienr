#include "mytcpsocket.h"


MyTcpSocket::MyTcpSocket(QString host, quint16 port) : QObject(nullptr)
{
    mTcpSocket = new QTcpSocket(this);

    mTcpSocket->connectToHost(host, port);

    connect(mTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(mTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );



}


void MyTcpSocket::slotReadyRead()
{
    QByteArray array;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array.append(mTcpSocket->readAll());
    }
    QString str = array;

    qDebug().noquote()  << str;
}

void MyTcpSocket::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(mTcpSocket->errorString())
                    );
    qDebug() << strError;
}


void MyTcpSocket::slotSendToServer(QString data)
{
    QByteArray arr;
    arr.append(data);
    mTcpSocket->write(arr);
}


void MyTcpSocket::slotConnected()
{
   qDebug() << "Received the connected() signal";
}
