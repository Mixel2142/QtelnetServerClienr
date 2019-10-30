#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{

    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 6000)){// порт 23 не получается
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }

}

void MyTcpServer::slotNewConnection()
{
    qDebug() << "New connection!\n";

    mTcpSocket = mTcpServer->nextPendingConnection();
    mTcpSocket->write("Hello, World!!! I am telnet server!\r\n");

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{

    QProcess mProcess;
    QByteArray array;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array.append(mTcpSocket->readAll());
    }

    QString strCommand = "";
#ifdef Q_WS_WIN
    strCommand = "cmd /C ";
#endif
    strCommand.append(array);

    if(strCommand.contains("exit") || strCommand.contains("quit")) {
        mTcpSocket->close();
        mProcess.close();
    }

    mProcess.start(strCommand);

    mProcess.waitForFinished();

    QByteArray outArray = mProcess.readAllStandardError() + " ";
    outArray.append(mProcess.readAllStandardOutput()+" ");
    mTcpSocket->write(outArray);
    mProcess.close();
    mProcess.kill();

}


void MyTcpServer::slotClientDisconnected()
{
    qDebug() << "Diconnect";
    mTcpSocket->close();
}
