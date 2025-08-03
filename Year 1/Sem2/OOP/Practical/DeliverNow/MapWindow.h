#pragma once
#include <QWidget>
#include <QPainter>
#include "Observer.h"
#include "Service.h"

class MapWindow : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;

public:
    MapWindow(Service& service, QWidget* parent = nullptr);
    void update() override;

protected:
    void paintEvent(QPaintEvent* event) override;
};
