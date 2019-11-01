#include "console.h"

Console::Console(QObject *parent) : QObject(parent)
{

#ifdef Q_OS_WIN
    mNotifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));
    connect(mNotifier,&QWinEventNotifier::activated
#else
    mNotifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read);
    connect(mNotifier,&QSocketNotifier::activated
#endif
    ,this, &Console::readCommand);

    std::cout << "Push Enter! ";
    std::cout.flush();
}

void Console::readCommand() {
    QTextStream qin(stdin);
    QString line = qin.readLine();

    if (line == "quit" || line == "exit")   {
        qDebug() << "Good bye!";
        emit textReceived(line);
        emit quit();
    } else {
        emit textReceived(line);
    }
}
