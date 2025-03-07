#include "sql/user_query.h"
#include "libpq-fe.h"
#include <string>

Query::Query(PGconn* conn) {
    m_conn = conn;
};

QByteArray Query::getUserPassword(std::string username) {
    std::string query = "SELECT password FROM users WHERE username = '" + username + "';";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return QByteArray();
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user found with username: " << username.c_str();
        PQclear(res);
        return QByteArray();
    }

    QByteArray hash = QByteArray(PQgetvalue(res, 0, 0));
    // std::string hashstr = (PQgetvalue(res, 0, 0));
    // qDebug() << "HASH FROM DB STR: " << hashstr << "\n";

    // QString hashStr = QString::fromUtf8(PQgetvalue(res, 0, 0)); // Получаем строку хеша
    // QByteArray hash = hashStr.toUtf8();
    // qDebug() << "HEX HASH DB: " << hash.toHex();
    PQclear(res);

    return hash;
}

PGresult* Query::getUserByID(int id) {
    std::string query = "SELECT COUNT(*) FROM users WHERE id = '" + std::to_string(id) + "';";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return nullptr;
    }

    return res;
}

std::string Query::getUserID(std::string username) {
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "';";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return "";
    }

    std::string id = PQgetvalue(res, 0, 0);

    return id;
}

bool Query::userExist(std::string username) {  
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "';";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return true;
    }
    
    std::string count = PQgetvalue(res, 0, 0);
    PQclear(res);

    return count != "0";
}

bool Query::isAdmin(std::string username) {
    std::string query = "SELECT is_admin FROM users WHERE username = '" + username + "';";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return false;
    }

    std::string isAdmin = PQgetvalue(res, 0, 0);
    PQclear(res);

    return (isAdmin == "true") ? true : false;
}
