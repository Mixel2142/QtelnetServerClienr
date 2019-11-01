#include <QCoreApplication>
#include "mytcpsocket.h"
#include "console.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    MyTcpSocket socket;

    Console console;

    QObject::connect(&console,SIGNAL(quit()),&app,SLOT(quit()));
    QObject::connect(&console,SIGNAL(textReceived(QString)),&socket,SLOT(slotSendToServer(QString)));

    return app.exec();
}
