#include <QCoreApplication>
#include "mytcpsocket.h"
#include "consolereader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpSocket socket;

    return a.exec();
}
