#pragma once

#include "Idea.h"
#include <QAbstractTableModel>
#include <vector>
class IdeaTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Idea> ideas;

public:
    IdeaTableModel(const std::vector<Idea>& ideas, QObject* parent = nullptr)
        : QAbstractTableModel(parent), ideas(ideas) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return static_cast<int>(ideas.size());
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;  // Description, Status, Creator, Act
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const Idea& idea = ideas.at(index.row());
            switch (index.column()) {
                case 0: return QString::fromStdString(idea.getDescription());
                case 1: return QString::fromStdString(idea.getStatus());
                case 2: return QString::fromStdString(idea.getCreator());
                case 3: return idea.getAct();
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "Description";
                case 1: return "Status";
                case 2: return "Creator";
                case 3: return "Act";
            }
        }
        return QVariant();
    }

    void setIdeas(const std::vector<Idea>& newIdeas) {
        beginResetModel();
        ideas = newIdeas;
        endResetModel();
    }

    const Idea& getIdeaAt(int row) const {
        return ideas.at(row);
    }
};
