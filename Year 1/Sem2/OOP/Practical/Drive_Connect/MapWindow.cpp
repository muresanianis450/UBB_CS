
#include "MapWindow.h"

MapWindow::MapWindow(ReportService& service, QWidget* parent)
    :QWidget(parent), service(service) {
    setWindowTitle("Map of valid reporst");
    resize(600,600);
    service.addObserver(this);

}

void MapWindow::update() {
    repaint();
}
void MapWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(),Qt::white);//fill background

    const double x_scale = width()/ 200.0;
    const double y_scale = height()/ 200.0;
    const int radius = 16;

    for (const auto& report: service.getReports()) {
        if (report.getIsValid()) {
            int x = static_cast<int>(report.getLongitude()*x_scale);
            int y = static_cast<int>(report.getLatitude()*y_scale);

            painter.setBrush(Qt::red);
            painter.drawEllipse(QPoint(x,y),radius,radius);
        }
    }

}