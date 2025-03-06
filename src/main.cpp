#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <exception>

#include "libpq-fe.h"
#include "pgconn.h"

int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml"))); 

    // db conn
    try {
        PGConnection db;

        if (db.connection()) {
            qDebug() << "db connected succesfully\n";
        } else {
            qDebug() << "failed to connect db\n";
            return 1;
        }

        PGresult* res = PQexec(db.connection().get(), "SELECT version();") ;
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            qDebug() << "PostgreSQL version: " << PQgetvalue(res, 0, 0) << "\n";
        } else {
            qDebug() << "Query failed: " << PQerrorMessage(db.connection().get()) << "\n";
        }
    } catch (const std::exception& e){
        qDebug() << "Exception: " << e.what() << "\n";
        return 1;
    }

    return app.exec();
}