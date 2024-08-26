#include "mainwindow.h"

#include <QApplication>
#include"../shared/sharedglobal.h"
#include"netloader.h"
#include"netclient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
