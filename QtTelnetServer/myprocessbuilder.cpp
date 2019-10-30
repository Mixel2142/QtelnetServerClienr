#include "myprocessbuilder.h"

QProcess* MyProcessBuilder::buildNewProcess()
{
    return ++proces= new QProcess();
}

