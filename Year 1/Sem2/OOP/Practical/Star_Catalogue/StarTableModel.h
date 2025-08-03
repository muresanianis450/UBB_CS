#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Star.h"
class StarTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    std::vector<Star> stars;
public:
    explicit StarTableModel(const std::vector<Star>& stars, QObject* parent = nullptr)
        :QAbstractTableModel(parent), stars(stars) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return static_cast<int>(stars.size());
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4; //name,RA,Dec,diameter
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
    if (!index.isValid() || index.row() >= stars.size() || role != Qt::DisplayRole){
        return QVariant();
    }

        const Star& star = stars[index.row()];
        if (index.column() == 0) {
            return QString::fromStdString(star.getName());
        }else
        if (index.column() == 1) {
            return star.getRA();
        }else
        if (index.column() == 2) {
            return star.getDec();
        }else
        if (index.column() == 3) {
            return star.getDiameter();
        }else
            return QVariant();
    }

    void setStars(const std::vector<Star>& newStar) {
        beginResetModel();
        stars = newStar;
        endResetModel();
    }
    Star getStarAt(int row) const {
        if (row < 0 || row >= static_cast<int>(stars.size())) {
            throw std::out_of_range("invalid row");
        }
        return stars[row];
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("RA");
                case 2:
                    return QString("Dec");
                case 3:
                    return QString("Diameter");
                default:
                    return QVariant();
            }
        }
        return QVariant();
    }


};