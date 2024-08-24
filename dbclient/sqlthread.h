#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QThreadPool>
#include <QRunnable>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QObject>
#include <QFutureWatcher>

class SqlThread {

public:
    explicit SqlThread();
    ~SqlThread();


    template<typename T,typename Func>
    QFuture<T> run(Func func)
    {
        return QtConcurrent::run(threadPool, func);
    }


private:
    QThreadPool *threadPool;

};

#endif // SQLTHREAD_H
