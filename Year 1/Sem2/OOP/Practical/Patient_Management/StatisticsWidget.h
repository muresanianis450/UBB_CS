#pragma once
#include <QWidget>
#include <map>
#include <QString>
#include "Observable.h"
#include "HospitalService.h"

class StatisticsWidget : public QWidget, public Observer {
    Q_OBJECT

private:
    HospitalService& service;
    std::map<QString, int> specializationCounts;

public:
    StatisticsWidget(HospitalService& service, QWidget* parent = nullptr);
    void update() override;

protected:
    void paintEvent(QPaintEvent* event) override;
};
