#ifndef QKINECT_H
#define QKINECT_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QPoint>
#include <QSize>
#include <QPair>
#include <QThread>
#include <QMutex>
#include <basetyps.h>
#include <WTypes.h>
#include <Windows.h>
#include <NuiApi.h>
#include <array>

#include "RectangleDetection.h"
#include "opencv2/core/core.hpp"

#define video_width 1280//640
#define video_height 960//480

class QSize;

class QKinect : public QThread
{
	Q_OBJECT

	//skeleton
	static const int cScreenWidth  = 320;
    static const int cScreenHeight = 240;

public:
	QKinect(QSize* screenSize);
	~QKinect();
	bool isKinectAvailable();
	inline bool isConnected() const { return m_connected; }
	inline bool isReady() const { return m_ready; }
	inline bool isCalibrated() const { return m_calibrated; }
	bool startKinect();
	void stopKinect();
	void setElevationAngle(int angle);

	void calibrate();

	QImage getFrameColorCamera();
	inline unsigned long getFrameColorSize() const { return m_frameColorSize; }
	inline BYTE* getFrameColorData() const { return m_frameColorData; }
	inline QList<QList<QPoint>>* getSkeleton() { return &m_skeletons; }
	QList<QList<QPoint>> getRealSkeletons();
	inline int getElevationAngle() const { return m_angle; }
	QString getStatutsDescription();
	QPair<int, int>  getHandsPosition();
	QList<QPoint> getCorners();

protected:
	void run();

signals:
	void updateInfo(QString);
	void newDatas();
	void calibrated();

private slots:
	void update();

private:
	static const int kNbImages = 10;
	bool init();
	void addImage();
	bool processSkeleton();
	bool processColor();
	void infos(QString);
	QPoint SkeletonToScreen(Vector4,int,int);

	INuiSensor* m_kinect; //Kinect device
	QSize* m_screenSize; //Size of the widget that use the kinect
	QPoint m_realScreenPosition;
	QSize m_realScreenSize;
	bool m_connected;
	bool m_run;
	int m_angle;
	int m_nbSkeletons;
	bool m_calibrated;
	bool m_ready;
	bool m_hasToCalibrate;
	QMutex mutex;

	std::array<cv::Point,4> m_points;

	//Color camera
    HANDLE m_pColorStreamHandle;
    HANDLE m_hNextColorFrameEvent;
	unsigned long m_frameColorSize; //Size of the image (just for be sure that the image is complete)
	BYTE* m_frameColorData;

	//Skeleton
    HANDLE m_pSkeletonStreamHandle;
    HANDLE m_hNextSkeletonEvent;
	QList<QList<QPoint>> m_skeletons;

	RectangleDetection m_rectangleDetection;
};


void drawSquares( cv::Mat& image, const std::array<cv::Point ,4>& squares );
#endif // QKINECT_H
