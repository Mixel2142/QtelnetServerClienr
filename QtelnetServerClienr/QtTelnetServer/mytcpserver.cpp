#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{

    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::LocalHost, 6000)){// порт 23 не получается
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }

}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
    qint64 mId = clientSocket->socketDescriptor();

    qDebug() << "New connection: " << mId;
    clientSocket->write("Hello, World!!! I am telnet server!\r\n");

    connect(clientSocket,&QTcpSocket::readyRead,this, &MyTcpServer::slotServerRead);
    connect(clientSocket,SIGNAL(disconnected()),this, SLOT(slotClientDisconnected()));

}

void MyTcpServer::slotServerRead()
{
    QProcess proc;
    proc.waitForStarted();
    QByteArray array;
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    while(clientSocket->bytesAvailable()>0)
    {
        array.append(clientSocket->readAll());
    }

    QString strCommand;
#ifdef Q_OS_WIN
    strCommand.append("cmd /C ");
#endif
    strCommand.append(array);

    proc.start(strCommand);
    proc.waitForFinished();

    if(strCommand.contains("exit") || strCommand.contains("quit")) {
        clientSocket->close();
    }

    QByteArray outArray = proc.readAllStandardError() + '\n';
    outArray.append(proc.readAllStandardOutput());
    clientSocket->write(outArray);
}


void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    qint64 idusersocs = clientSocket->socketDescriptor();
    qDebug() << "Diconnect: " << idusersocs;
    clientSocket->close();
}
