#include "TaskModel.h"
#include <QString>
#include <algorithm>

TaskModel::TaskModel(QObject* parent) : QAbstractTableModel(parent) {}

void TaskModel::setTasks(const std::vector<Task>& newTasks) {
    beginResetModel();
    tasks = newTasks;

    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        std::map<std::string, int> statusPriority = {
            {"open", 0}, {"in progress", 1}, {"closed", 2}
        };
        return statusPriority[a.getStatus()] < statusPriority[b.getStatus()];
    });
    endResetModel();
}
int TaskModel::rowCount(const QModelIndex& ) const {
    return static_cast<int>(tasks.size());
}
int TaskModel::columnCount(const QModelIndex&) const {
    return 3;
}
QVariant TaskModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    const Task &task = tasks[index.row()];
    if (index.column() == 0) {
        return QString::fromStdString(task.getDescription());
    } else
        if (index.column() == 1) {
        return QString::fromStdString(task.getStatus());
    } else
        if (index.column() == 2) {
        if (task.getProgrammerId() == -1) {
            return QString{"unassigned"};
        } else {
            return task.getProgrammerId();
        }
    } else {
        return QVariant();
    }
}

QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    if (section == 0) {
        return QString("Description");
    } else if (section == 1) {
        return QString("Status");
    } else if (section == 2) {
        return QString("Programmer ID");
    } else {
        return QVariant();
    }
}
Qt::ItemFlags TaskModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void TaskModel::refresh(const std::vector<Task>& updatedTasks) {
    setTasks(updatedTasks);
}


