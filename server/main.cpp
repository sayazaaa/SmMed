#include <QCoreApplication>
//#include <include/dbserver.h>
#include <shared_global.h>
#include <shared.h>
#include <include/dbserver.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try {
        throw (DbException());
    } catch (DbException e) {
        printf("%s\n",e.what());
    }
    return a.exec();
}
