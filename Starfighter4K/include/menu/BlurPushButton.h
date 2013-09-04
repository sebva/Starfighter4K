#ifndef BLURPUSHBUTTON_H
#define BLURPUSHBUTTON_H

class BlurPushButton : public QPushButton
{
	Q_OBJECT

public:
	BlurPushButton(QWidget *parent);
	~BlurPushButton();
	static QImage blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly);
	void setHandOnTop(bool isOnTop);

protected:
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	static QImage original;
	QPixmap blur;
	QImage background;
	bool handOnTop;
	qreal progress;
	QTimer timer;

private slots:
	void clockTick();
};

#endif // BLURPUSHBUTTON_H
