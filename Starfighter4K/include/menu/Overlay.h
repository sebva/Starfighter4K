#ifndef OVERLAY_H
#define OVERLAY_H

class Overlay : public QWidget
{
public:
    Overlay(QWidget *parent);
	void setHands(QPair<QPoint, QPoint> hands);
 
protected:
    void paintEvent(QPaintEvent *event);

private:
	QPoint hand1;
	QPoint hand2;
};

#endif // OVERLAY_H
