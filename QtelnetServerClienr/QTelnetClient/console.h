#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <iostream>
#include <QTextStream>
#include <QDebug>

#ifdef Q_OS_WIN
#include <QWinEventNotifier>
#include <Windows.h>
#else
#include <QSocketNotifier>
#endif


class Console : public QObject
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);
    void run();

signals:
    void quit();
    void textReceived(QString message);
private slots:
    void readCommand();

private:
#ifdef Q_OS_WIN
    QWinEventNotifier *mNotifier;
#else
    QSocketNotifier *mNotifier;
#endif
};


#endif // CONSOLE_H
