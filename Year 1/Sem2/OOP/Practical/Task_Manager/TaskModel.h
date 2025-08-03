#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Task.h"

class TaskModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Task> tasks;
public:
    TaskModel(QObject* parent= nullptr);

    void setTasks(const std::vector<Task>& tasks);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void refresh(const std::vector<Task>& updatedTasks);

};