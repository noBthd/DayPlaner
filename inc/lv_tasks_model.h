#ifndef LV_TASKS_MODEL
#define LV_TASKS_MODEL

#include <QAbstractListModel>
#include <QList>
#include "task.h"

class LVTask : public QAbstractListModel {
    Q_OBJECT;

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            NameRole,
            TextRole, 
            StatusRole
        };

        explicit LVTask(QObject* parent = nullptr); 

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;
        QHash<int, QByteArray> roleNames() const override;
    
        void addTask(Task* task);
        void removeTask(int task_id);
        void clear();

    private:
        QList<Task*> m_tasks;
};

#endif