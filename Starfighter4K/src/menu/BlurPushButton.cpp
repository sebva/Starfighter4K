#include "include/menu/BlurPushButton.h"

BlurPushButton::BlurPushButton(QWidget *parent)
	: QPushButton(parent), original(":/images/menu/background")
{
	setStyleSheet("*{background-color:rgba(0,0,0,0);}");
}

BlurPushButton::~BlurPushButton()
{

}

void BlurPushButton::resizeEvent(QResizeEvent* event)
{
	background = blurred(original, QRect(mapToGlobal(rect().topLeft()), event->size()), 20, false);
	blur = QPixmap(event->size());
	blur.fill(QColor(168,195,205,20*2.55));

	event->accept();
}

void BlurPushButton::paintEvent(QPaintEvent *event)
{
	QPainter p(this);

	QPoint point = mapToGlobal(rect().topLeft());
	p.drawImage(0, 0, background);//, point.x(), point.y());
	
	p.drawPixmap(0, 0, blur);

	QPushButton::paintEvent(event);
}

// From: http://stackoverflow.com/questions/3903223/qt4-how-to-blur-qpixmap-image
QImage BlurPushButton::blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly)
{
	int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
	int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

	QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
	int r1 = rect.top();
	int r2 = rect.bottom();
	int c1 = rect.left();
	int c2 = rect.right();

	int bpl = result.bytesPerLine();
	int rgba[4];
	unsigned char* p;

	int i1 = 0;
	int i2 = 3;

	if (alphaOnly)
	i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

	for (int col = c1; col <= c2; col++) {
		p = result.scanLine(r1) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += bpl;
		for (int j = r1; j < r2; j++, p += bpl)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c1 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += 4;
		for (int j = c1; j < c2; j++, p += 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int col = c1; col <= c2; col++) {
		p = result.scanLine(r2) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= bpl;
	for (int j = r1; j < r2; j++, p -= bpl)
		for (int i = i1; i <= i2; i++)
			p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result.scanLine(row) + c2 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= 4;
		for (int j = c1; j < c2; j++, p -= 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	return result.copy(rect);
}
