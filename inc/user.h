#ifndef USER_H
#define USER_H

#include "sql/user_query.h"
#include "utils/passwordUtils.h"
#include <string>
#include <QByteArray>
#include <QDebug>

class User {
    public:
        User(std::string, std::string, Query*);

        bool isAdmin();
        bool exists();
        bool login();
        void getHash();
        bool regUser();
        std::string getUsername();

    private:
        Query* m_query;

        int m_id;
        std::string m_username;
        Password m_password;
        bool m_admin;
};

#endif