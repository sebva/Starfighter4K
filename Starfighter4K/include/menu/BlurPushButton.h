#ifndef BLURPUSHBUTTON_H
#define BLURPUSHBUTTON_H

class BlurPushButton : public QPushButton
{
	Q_OBJECT

public:
	BlurPushButton(QWidget *parent);
	~BlurPushButton();
	static QImage blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly);

protected:
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	QImage original;
	QPixmap blur;
	QImage background;
};

#endif // BLURPUSHBUTTON_H
