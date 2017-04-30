#ifndef LOGSQL_H
#define LOGSQL_H
//
#include <qt5/QtSql/QtSql>
#include <qt5/QtSql/QSqlDatabase>
#include <qt5/QtCore/QString>
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtNetwork/QNetworkAccessManager>
#include <qt5/QtCore/QTextStream>
#include "csv.h"
//
class LogSql : public QObject
{
    Q_OBJECT

public:
    LogSql(QString dbName="airLog.db3");
    virtual ~LogSql();

    QSqlDatabase &getDb() {
        return _db;
    }

    void updateOnline(QString url,QString table);

private:
    void checkTables();

    QSqlDatabase _db;

};
#endif
