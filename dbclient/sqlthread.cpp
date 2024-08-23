#include "sqlthread.h"

SqlThread::SqlThread(): threadPool(new QThreadPool())
{
    threadPool->setMaxThreadCount(8);
}
SqlThread::~SqlThread()
{
    threadPool->waitForDone();
}



