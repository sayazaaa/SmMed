#include "DBManager.h"



QSqlDatabase& DatabaseManager::getDatabase() {
    return database;
}

DatabaseManager::DatabaseManager() {
    // Initialize the SQLite database
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("user.sqlite");

    // Open the database
    if (!database.open()) {
        qDebug() << "Failed to open database:" << database.lastError().text();
        return;
    }

    QSqlQuery query(database);
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS chat_messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender_id VARCHAR(128) NOT NULL,
            receiver_id VARCHAR(128) NOT NULL,
            message TEXT NOT NULL,
            timestamp TEXT NOT NULL
        )
    )";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Failed to create table:" << query.lastError();
    } else {
        qDebug() << "Table created successfully or already exists.";
    }

}

DatabaseManager::~DatabaseManager() {
    database.close();
}
