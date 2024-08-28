#include <QtSql>

class DatabaseManager {
public:
    static DatabaseManager& getInstance() {
        static DatabaseManager instance;
        return instance;
    }

    QSqlDatabase& getDatabase() ;

private:
    DatabaseManager();

    ~DatabaseManager() ;

    QSqlDatabase database;
};

