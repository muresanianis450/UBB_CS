#pragma once
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QPainter>
#include <vector>
#include "Service.h"
#include "StarTableModel.h"
#include "Observable.h"


class StarWindow :public QWidget, public Observer {
    Q_OBJECT
private:
    Service& service;
    Astronomer astronomer;

    QTableView* starTableView;
    StarTableModel* starModel;

    QCheckBox* filterCheckBox;
    QLineEdit* searchLineEdit;

    QLineEdit* nameLineEdit;
    QLineEdit* raLineEdit;
    QLineEdit* decLineEdit;
    QLineEdit* diamterLineEdit;
    QPushButton* addStarButton, * viewButton;

    std::vector<Star> currentStars;

    void updateModelWithFilterAndSearch();

public:

    StarWindow(Service& service, const Astronomer& astronomer, QWidget* parent = nullptr);

    ~StarWindow() = default ;

    void update() override;

    private slots:
    void handleFilter(bool checked);
    void handleSearchTextChanged(const QString& text);
    void handleAddStar();
    void handleViewStar();
};