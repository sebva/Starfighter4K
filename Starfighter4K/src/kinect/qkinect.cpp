#include "include/kinect/qkinect.h"
#include <QDebug>

#define WORK "The device is connected and work."
#define REFRESH_FREQUENCY 1000 / 30 // 30 fps

using namespace cv;
using namespace std;

QKinect::QKinect(QSize* screenSize) :
	m_screenSize(screenSize),
	m_kinect(nullptr),
    m_hNextSkeletonEvent(INVALID_HANDLE_VALUE),
    m_pSkeletonStreamHandle(INVALID_HANDLE_VALUE),
	m_hNextColorFrameEvent(INVALID_HANDLE_VALUE),
	m_pColorStreamHandle(INVALID_HANDLE_VALUE),
	m_frameColorSize(0),
	m_frameColorData(nullptr),
	m_connected(false),
	m_run(false),
	m_nbSkeletons(0),
	m_calibrated(false),
	m_ready(false),
	m_hasToCalibrate(false)
{
	m_ready = init();
}

QKinect::~QKinect()
{
	infos("destroy");
	if (m_kinect)
        m_kinect->NuiShutdown(); //Shutdown the kinect
}

bool QKinect::isKinectAvailable()
{
	int numSensors;
	return NuiGetSensorCount(&numSensors) == S_OK && numSensors > 0; //test if there is a kinect connected to the pc and available
}

bool QKinect::startKinect()
{
	infos("Kinect starting...");
	if(m_kinect == nullptr || !m_ready) m_ready = init();

	if(isConnected() && m_ready)
	{
		start();
		return true;
	}
	return false;
}

void QKinect::stopKinect()
{
	m_run = false;
}

void QKinect::setElevationAngle(int angle)
{
	m_angle = angle;
	m_kinect->NuiCameraElevationSetAngle(m_angle);
}

void QKinect::calibrate()
{
	m_hasToCalibrate = true;
}

void drawSquares( Mat& image, const std::array<cv::Point ,4>& points )
{
	for(auto it = points.begin(); it != points.end(); ++it)
	{
		circle(image, *it, 10, Scalar(255, 255, 255), 3);
    }

    cv::imshow("Detection", image);
}

QImage QKinect::getFrameColorCamera()
{
	QImage image = QImage(m_frameColorData, video_width, video_height, QImage::Format::Format_RGB32);
	if(m_frameColorSize > (video_width - 1) * video_height * 4)
		image.scaled(*m_screenSize, Qt::AspectRatioMode::KeepAspectRatio);
	else
		image.fill(Qt::white);

	return image;
}

QList<QList<QPoint>> QKinect::getRealSkeletons()
{
	QMutexLocker locker(&mutex);
	QList<QList<QPoint>> realSkeletons;
	
	double xRatio = (m_realScreenSize.width() / (double)video_width);
	double yRatio = (m_realScreenSize.height() / (double)video_height);
	
	for(QList<QPoint> skeleton : m_skeletons)
	{
		if(skeleton.count() >= 20)
		{
			QList<QPoint> realSkeleton;
			for(QPoint point : skeleton)
			{
				double x1 = (point.x() / (double)m_screenSize->width());
				double x2 = (m_realScreenPosition.x() / (double)video_width);
				double y1 = (point.y() / (double)m_screenSize->height());
				double y2 = (m_realScreenPosition.y() / (double)video_height);
				realSkeleton << QPoint(((x1 - x2) / xRatio) * m_screenSize->width(), ((y1 - y2) / yRatio) * m_screenSize->height());
				//qDebug() << "x1" << x1 << "\tx2" << x2 << "\ty1" << y1 << "\ty2" << y2 << "\txratio" << xRatio << "\tyRatio" << yRatio;
				//qDebug() << "\nm_realScreenSize.width()" << m_realScreenSize.width() << "\tm_realScreenSize.height()" << m_realScreenSize.height() << "\tpoint.x()" << point.x() << "\tpoint.y()" << point.y() << "\txratio" << xRatio << "\tyRatio" << yRatio;
			}
			realSkeletons << realSkeleton;
		}
	}

	return realSkeletons;
}

QString QKinect::getStatutsDescription()
{
	if(m_kinect == nullptr) return "Kinect not initialized";
	if(!isKinectAvailable()) return "No Kinect available";
	switch (m_kinect->NuiStatus())
	{
	case S_OK :
		return WORK;
	case S_NUI_INITIALIZING :
		return "The device is connected, but still initializing.";
	case E_NUI_NOTCONNECTED :
		return "The device is not connected.";
	case E_NUI_NOTGENUINE :
		return "The device is not a valid Kinect.";
	case E_NUI_NOTSUPPORTED :
		return "The device is an unsupported model.";
	case E_NUI_INSUFFICIENTBANDWIDTH :
		return "The device is connected to a hub without the necessary bandwidth requirements.";
	case E_NUI_NOTPOWERED :
		return "The device is connected, but unpowered.";
	case E_NUI_NOTREADY :
		return "There was some other unspecified error.";
	}
	return "error";
}

QPair<QPoint, QPoint> QKinect::getHandsPosition()
{
	QPair<QPoint, QPoint> hands;
	
	for(QList<QPoint> skeleton : getRealSkeletons())
	{
		if(skeleton.count() >= 20)
		{
			if(skeleton[NUI_SKELETON_POSITION_HEAD].x() < m_screenSize->width() / 2)
				hands.second = (skeleton[NUI_SKELETON_POSITION_HAND_RIGHT].x() < skeleton[NUI_SKELETON_POSITION_HAND_LEFT].x()) ? skeleton[NUI_SKELETON_POSITION_HAND_RIGHT] : skeleton[NUI_SKELETON_POSITION_HAND_LEFT];
			else
				hands.first = (skeleton[NUI_SKELETON_POSITION_HAND_RIGHT].x() > skeleton[NUI_SKELETON_POSITION_HAND_LEFT].x()) ? skeleton[NUI_SKELETON_POSITION_HAND_RIGHT] : skeleton[NUI_SKELETON_POSITION_HAND_LEFT];
		}
	}

	return hands;
}

QList<QPoint> QKinect::getCorners()
{
	QList<QPoint> corners;
	
	double xRatio = (double)m_screenSize->width() / video_width;
	double yRatio = (double)m_screenSize->height() / video_height;

	for(Point point : m_points)
	{
		corners << QPoint(point.x * xRatio, point.y * yRatio);
	}

	return corners;
}

void QKinect::run()
{
	m_run = true;
	while(m_run)
	{
		update();
		QThread::msleep(REFRESH_FREQUENCY);
	}
}

void QKinect::update()
{
	if(m_kinect == nullptr) return;
	bool update = (m_calibrated) ? false : processColor();
	update |= processSkeleton();
	if(update)
		emit newDatas();
	qDebug() << *m_screenSize;
}

bool QKinect::init()
{
    if (!isKinectAvailable()) return false;
	if (NuiCreateSensorByIndex(0, &m_kinect) < 0) return false; //Fail to create connection to the kinect

    // Initialize sensor
	HRESULT hr = m_kinect->NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON); // initialize the kinect for skeletion and color, it's possible to add more than only the skeletion (e.g. camera)
	if (SUCCEEDED(hr))
    {
        // Open a skeleton stream to receive skeleton data
		hr = m_kinect->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, 0); //NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE);
		if (FAILED(hr))
			infos("fail to open a skeleton stream");
		else
		{
			 // Create an event that will be signaled when skeleton data is available
			m_hNextSkeletonEvent = CreateEventW(0, TRUE, FALSE, 0);
        
			// Open a skeleton stream to receive skeleton data
			hr = m_kinect->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, 0); 
		}

		 // Create an event that will be signaled when color data is available
		m_hNextColorFrameEvent = CreateEvent(0, TRUE, FALSE, 0);

		hr = m_kinect->NuiImageStreamOpen(
			NUI_IMAGE_TYPE_COLOR,            // Depth camera or rgb camera?
			NUI_IMAGE_RESOLUTION_1280x960,    // Image resolution
			0,      // Image stream flags, e.g. near mode
			2,      // Number of frames to buffer
			m_hNextColorFrameEvent,   // Event handle
			&m_pColorStreamHandle);
		
		if (FAILED(hr))
			infos("fail to open a color stream");
		else
			infos("A color stream is open");
		m_connected = true;
    }
	else
		infos("fail to open initialize kinect");

	setElevationAngle(7);

	//m_kinect->colorstream

	return getStatutsDescription() == WORK;
}

void QKinect::addImage()
{
	static int i = 1;
	infos(QString("Image %1").arg(i++));
	Mat mat(video_height,video_width,CV_8UC4,m_frameColorData);
	m_rectangleDetection.addImage(mat);

	if(m_rectangleDetection.getSizeImages() == kNbImages)
	{
		m_hasToCalibrate = false;
		m_calibrated = true;

		m_points = m_rectangleDetection.getPoints();
		m_realScreenPosition = QPoint(m_points[0].x, m_points[0].y);
		m_realScreenSize = QSize(m_points[2].x - m_points[0].x, m_points[2].y - m_points[0].y);

		emit calibrated();
		

		if (m_hNextColorFrameEvent != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hNextColorFrameEvent);
		}
		qDebug() << QPoint(m_points[0].x, m_points[0].y) << QPoint(m_points[1].x, m_points[1].y) << QPoint(m_points[2].x, m_points[2].y) << QPoint(m_points[3].x, m_points[3].y);
		qDebug() << m_realScreenPosition << m_realScreenSize;

	}
}

bool QKinect::processSkeleton()
{
	QMutexLocker locker(&mutex);
    NUI_SKELETON_FRAME skeletonFrame = {0};

	HRESULT hr = m_kinect->NuiSkeletonGetNextFrame(0, &skeletonFrame); // get the new skeleton infos
	if (FAILED(hr)) { infos("fail NuiSkeletonGetNextFrame"); return false; }

    // smooth out the skeleton data
    m_kinect->NuiTransformSmooth(&skeletonFrame, NULL);

	m_nbSkeletons = 0;

	int width = m_screenSize->width();
	int height = m_screenSize->height();
	
	m_skeletons.clear();
	for (int i = 0 ; i < NUI_SKELETON_COUNT; ++i) //fetch the skeletons
    {
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
		
		QList<QPoint> skeleton;

        if (NUI_SKELETON_TRACKED == trackingState)
        {
            // We're tracking the skeleton
			for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j)
			{
				skeleton << SkeletonToScreen(skeletonFrame.SkeletonData[i].SkeletonPositions[j], width, height);
			}
			m_nbSkeletons++;
		
        }
        else if (NUI_SKELETON_POSITION_ONLY == trackingState)
        {
            // we've only received the center point of the skeleton
			skeleton << SkeletonToScreen(skeletonFrame.SkeletonData[i].Position, width, height);
		}
		m_skeletons << skeleton;
	}

	infos(QString("%1 bitche(s) in front of the kinect").arg(m_nbSkeletons));

	return true;
}

bool QKinect::processColor()
{
    HRESULT hr;
    NUI_IMAGE_FRAME imageFrame;

    // Attempt to get the color frame
	hr = m_kinect->NuiImageStreamGetNextFrame(m_pColorStreamHandle, 0, &imageFrame);
	if (FAILED(hr)) { infos("fail NuiImageStreamGetNextFrame"); return false; }

    INuiFrameTexture* pTexture = imageFrame.pFrameTexture;
    NUI_LOCKED_RECT lockedRect;

    // Lock the frame data so the Kinect knows not to modify it while we're reading it
    pTexture->LockRect(0, &lockedRect, 0, 0);

    // Make sure we've received valid data
    if (lockedRect.Pitch != 0)
    {
        // Get the datas
		m_frameColorData = static_cast<BYTE *>(lockedRect.pBits);
		m_frameColorSize = lockedRect.size;
		if(m_hasToCalibrate && !m_calibrated)
			addImage();
    }

    // We're done with the texture so unlock it
    pTexture->UnlockRect(0);

    // Release the frame
    m_kinect->NuiImageStreamReleaseFrame(m_pColorStreamHandle, &imageFrame);

	return true;
}

void QKinect::infos(QString message)
{
	int val = 0;
	NuiGetSensorCount(&val);
	
	message = QString("%1 | %2 | %3 Kinect(s) available").arg(message).arg(getStatutsDescription()).arg(val);
	emit updateInfo(message);
}

/// <summary>
/// Converts a skeleton point to screen space
/// </summary>
/// <param name="skeletonPoint">skeleton point to tranform</param>
/// <param name="width">width (in pixels) of output buffer</param>
/// <param name="height">height (in pixels) of output buffer</param>
/// <returns>point in screen-space</returns>
QPoint QKinect::SkeletonToScreen(Vector4 skeletonPoint, int width, int height)
{
    LONG x, y;
    USHORT depth;

    // Calculate the skeleton's position on the screen
    // NuiTransformSkeletonToDepthImage returns coordinates in NUI_IMAGE_RESOLUTION_320x240 space
    NuiTransformSkeletonToDepthImage(skeletonPoint, &x, &y, &depth);
	//qDebug() << QString("(%1,%2) - %3").arg(x).arg(y);
	//qDebug() << QString("w: %1, x: %2, y: %3, z: %4").arg(skeletonPoint.w).arg(skeletonPoint.x).arg(skeletonPoint.y).arg(skeletonPoint.z);

	float screenPointX = static_cast<float>(x * width) / cScreenWidth;
	float screenPointY = static_cast<float>(y * height) / cScreenHeight;

    return QPoint(screenPointX, screenPointY);
}
