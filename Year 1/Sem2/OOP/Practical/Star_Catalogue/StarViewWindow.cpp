#include "StarViewWindow.h"

StarViewWindow::StarViewWindow(const std::vector<Star>& stars, const Star& selectedStar, QWidget* parent)
	: QDialog(parent), stars(stars), selectedStar(selectedStar) {

setWindowTitle("Stars in contelation: "+ QString::fromStdString(selectedStar.getConstelation()));
	resize(600,600);
}
void StarViewWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);

	if (stars.empty())
		return;

	// find min/max RA and DEC for scaling
	int minRA = stars[0].getRA(), maxRA = stars[0].getRA();
	int minDec = stars[0].getDec(), maxDec = stars[0].getDec();

	for (const auto& star : stars) {
		if (star.getRA() < minRA) minRA = star.getRA();
		if (star.getRA() > maxRA) maxRA = star.getRA();
		if (star.getDec() < minDec) minDec = star.getDec();
		if (star.getDec() > maxDec) maxDec = star.getDec();
	}

	int w = width() - 2 * padding;
	int h = height() - 2 * padding;


	int raRange = maxRA - minRA;
	int decRange = maxDec - minDec;


	for (const auto& star : stars) {
		int x = padding + (star.getRA() - minRA) * w / raRange;
		int y = padding + h - (star.getDec() - minDec) * h / decRange;

		int radius = star.getDiameter();

		if (star.getName() == selectedStar.getName()) {
			painter.setBrush(Qt::red);
		} else {
			painter.setBrush(Qt::black);
		}
		painter.drawEllipse(QPointF(x, y), radius, radius);
	}
}
