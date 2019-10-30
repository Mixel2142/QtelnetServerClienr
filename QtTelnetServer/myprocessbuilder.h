#ifndef MYPROCESSBUILDER_H
#define MYPROCESSBUILDER_H

#include <QObject>
#include <QProcess>

class MyProcessBuilder : public QObject
{
    Q_OBJECT
public:
    explicit MyProcessBuilder(QObject *parent = nullptr):QObject(parent){}

    QProcess* buildNewProcess();

private:
   QProcess* process;
};

#endif // MYPROCESSBUILDER_H
