#include "StatisticsWidget.h"
#include <QPainter>
#include <QColor>
#include <QFont>

StatisticsWidget::StatisticsWidget(HospitalService& service, QWidget* parent)
    : QWidget(parent), service(service) {
    service.addObserver(this);
    update();
}

void StatisticsWidget::update() {
    specializationCounts.clear();
    for (const auto& patient : service.getAllPatients()) {
        QString key = QString::fromStdString(
            patient.getDiagnosis() == "undiagnosed" ? "undiagnosed" : patient.getNeededSpecialization()
        );
        specializationCounts[key]++;
    }
    repaint();
}

void StatisticsWidget::paintEvent(QPaintEvent* /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    int total = 0;
    for (const auto& pair : specializationCounts)
        total += pair.second;

    if (total == 0) return;

    int x = 20, y = 20;
    int maxWidth = width() - 60;
    int barHeight = 40;
    int colorIndex = 0;

    for (const auto& [specialization, count] : specializationCounts) {
        double proportion = static_cast<double>(count) / total;
        int barWidth = static_cast<int>(proportion * maxWidth);

        QColor color = QColor::fromHsv((colorIndex++ * 60) % 360, 200, 255);
        painter.setBrush(color);
        painter.setPen(Qt::black);
        painter.drawRect(x, y, barWidth, barHeight);

        QString label = QString("%1 (%2)").arg(specialization, QString::number(count));
        painter.drawText(x + 5, y + barHeight / 2 + 5, label);

        y += barHeight + 15;
    }
}
