#ifndef TASK_H
#define TASK_H

#include <string>
#include <QDebug>
#include "libpq-fe.h"

class Task {
    public: 
        Task(
            PGconn* conn = nullptr,
            std::string* name = nullptr, 
            std::string* text = nullptr
        );

        ~Task();

        int getID();
        std::string* getTaskName();
        std::string* getTaskText();
        std::string* getTime();
        std::string* getStatus();
        bool getDone();
        bool getExpire();

        void setID(int);
        void setTaskName(std::string*);
        void setTaskText(std::string*);
        void setTime(std::string*);
        void setStatus(std::string*);
        void setDone(bool);
        void setExpired(bool);

        void done();
        void expired();

        private:
        PGconn* m_conn;
        
        // time
        int m_id;
        std::string* m_task_name;
        std::string* m_task_text;
        std::string* m_status;
        std::string* m_time;
        
        // done/not 
        bool m_done = false; 
        // expired/not
        bool m_expired = false;
        
        void setNewId();
        int getPrevId();

};

#endif