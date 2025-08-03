#pragma once

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Service.h"
#include "IdeaTableModel.h"
#include "Writer.h"
#include "Observer.h"
class ScreenwritingGUI : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;
    Writer writer;

    IdeaTableModel* model;
    QTableView* tableView;

    QLineEdit* descEdit;
    QLineEdit* actEdit;

    QPushButton* addButton;
    QPushButton* acceptButton;
    QPushButton* developButton;
    QPushButton* savePlotButton;



    void update() override;
    private slots:
    void handleAddIdea();
    void handleAcceptIdea();
    void handleSavePlot();

public:
    ScreenwritingGUI(Service& service, const Writer& writer, QWidget* parent = nullptr);
};
