#include "sql/user_query.h"
#include "libpq-fe.h"
#include "utils/passwordUtils.h"
#include <string>

Query::Query(PGconn* conn) {
    m_conn = conn;
};

void Query::createUser(std::string username, Password password, bool admin) {
    std::string str_admin = admin ? "true" : "false";
    std::string query = "INSERT INTO users(username, password, is_admin) VALUES ('" + username + "', '" + password.hashed_password + "', '" + str_admin + "')";

    if (userExist(username)) {
        qDebug() << "User already exists";
        return;
    }

    if (!password.isStrong()) {
        qDebug() << "Password isn't strong enough";
        return;
    }

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn);
        PQclear(res);
        return;
    }

    qDebug() << "User created succesfully";
    PQclear(res);

    return;
}

std::string Query::getUserPassword(std::string username) {
    std::string query = "SELECT password FROM users WHERE username = '" + username + "';";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return NULL;
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user found with username: " << username.c_str();
        PQclear(res);
        return NULL;
    }

    std::string hash = PQgetvalue(res, 0, 0);
    PQclear(res);

    return hash;
}

//! fix query 
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
    std::string query = "SELECT id FROM users WHERE username = '" + username + "';";
    
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

    return (isAdmin == "t") ? true : false;
}
