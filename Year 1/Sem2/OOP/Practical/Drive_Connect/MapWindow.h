#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "Observer.h"
#include "ReportService.h"

class MapWindow:public QWidget, public Observer {
Q_OBJECT
private:
    ReportService& service;

public:
    explicit MapWindow(ReportService& service, QWidget* parent = nullptr);
    void update() override;
    void paintEvent(QPaintEvent* event) override;
};