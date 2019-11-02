#include <QCoreApplication>
#include "mytcpsocket.h"
#include "console.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    const QString host = argc>1 ? QString(argv[1]):QString("127.0.0.1");
    const quint16 port = argc>2 ? QString(argv[2]).toUShort():QString("6000").toUShort();

    MyTcpSocket socket(host,port);

    Console console;

    QObject::connect(&console,SIGNAL(quit()),&app,SLOT(quit()));

    QObject::connect(&console,SIGNAL(textReceived(QString)),&socket,SLOT(slotSendToServer(QString)));

    return app.exec();
}
