#pragma once
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QPainter>
#include <QDialog>
#include <vector>
#include "StarTableModel.h"


class StarViewWindow: public QDialog {
    Q_OBJECT

private:
    std::vector<Star> stars;
    Star selectedStar;
    int padding = 20;

public:
    StarViewWindow(const std::vector<Star>& stars, const Star& selectedStar, QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event ) override;
};
