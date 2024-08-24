#include "mainwindow.h"

#include <QApplication>
#include"../shared/sharedglobal.h"
#include"netloader.h"
#include"netclient.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NetClient client;
    return a.exec();
}
