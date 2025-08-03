#include "MapWindow.h"
#include <QPainter>
#include <QBrush>

MapWindow::MapWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setWindowTitle("Package Map");
    service.addObserver(this);
    setMinimumSize(600, 400);
}

void MapWindow::update() {
    repaint();
}

void MapWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto& packages = service.getPackages();

    double maxX = 1;
    double maxY = 1;
    for (const auto& package : packages) {
        if (package.isDelivered()) continue;
        if (package.getX() > maxX) maxX = package.getX();
        if (package.getY() > maxY) maxY = package.getY();
    }


    int margin = 40;
    int width = this->width() - 2 * margin;
    int height = this->height() - 2 * margin;

    for (const auto& package : packages) {
        if (package.isDelivered()) continue;
        int x = margin + static_cast<int>((package.getX() / maxX) * width);
        int y = margin + static_cast<int>((package.getY() / maxY) * height);

        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(x - 10, y - 10, 20, 20);

        painter.setPen(Qt::black);
        painter.drawText(x + 15, y, QString::fromStdString(package.getRecipient()));
    }
}