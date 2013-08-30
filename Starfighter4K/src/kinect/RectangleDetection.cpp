#include "include/kinect/RectangleDetection.h"

#include "opencv2/imgproc/imgproc.hpp"

#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

RectangleDetection::RectangleDetection(int _thresh, int _N):thresh(_thresh),N(_N)
{

}

void RectangleDetection::addImage(const Mat& image)
{
	if(!image.empty())
	{
		images.push_back(Mat(image));
		points.push_back(vector<vector<Point>>());	
	}
}

bool sortPoint(const Point& p1, const Point& p2)
{
	return p1.x < p2.x || p2.y < p2.y;
}

array<Point, 4> RectangleDetection::getPoints()
{
	vector<vector<int>> pointsSort(8);
	bool isThereMinimumOneSquare = false;
	for(size_t i = 0;i < images.size(); ++i)
	{
		bool squaresfound = findSquares(images[i], points[i], thresh, N);
		isThereMinimumOneSquare |= squaresfound;
		if(squaresfound)
		{
			findLargestSquare(points[i]);
			sort(points[i][0].begin(),points[i][0].end(),sortPoint);

			for(int j = 0; j < 4; ++j)
			{
				pointsSort[2*j].push_back(points[i][0][j].x);//x0y0 -> x0
				pointsSort[2*j+1].push_back(points[i][0][j].y);//x0y0 -> y0
			}
		}
	}

	array<Point, 4> ret;
	if(isThereMinimumOneSquare)
	{
		for(int i = 0; i < 8; ++i)
			sort(pointsSort[i].begin(),pointsSort[i].end());

		bool even = images.size()-1 % 2 == 0;
		for(int i = 0; i < 4; ++i)
			ret[i] = (even) ? Point(pointsSort[2*i][images.size()/2],pointsSort[2*i+1][images.size()/2]) : Point(pointsSort[2*i][images.size()/2+1],pointsSort[2*i+1][images.size()/2+1]);
	}
	else
		for(int i = 0; i < 4; ++i)
			ret[i] = Point(0,0);
	return ret;
}

bool findSquares(const Mat& image, vector<vector<Point> >& squares, int thresh, int N)
{
    // blur will enhance edge detection
    Mat blurred(image);
    medianBlur(image, blurred, 9);

    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;

    // find green squares
    int ch[] = {1, 0};//Green channel
    mixChannels(&blurred, 1, &gray0, 1, ch, 1);

    // try several threshold levels
    const int threshold_level = 15;
    for (int l = 0; l < threshold_level; l++)
    {
        // Use Canny instead of zero threshold level!
        // Canny helps to catch squares with gradient shading
        if (l == 0)
        {
            Canny(gray0, gray, 10, 20, 3); // 

            // Dilate helps to remove potential holes between edge segments
            dilate(gray, gray, Mat(), Point(-1,-1));
        }
        else
        {
                gray = gray0 >= (l+1) * 255 / threshold_level;
        }

        // Find contours and store them in a list
        findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

        // Test contours
        vector<Point> approx;
        for (size_t i = 0; i < contours.size(); i++)
        {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 &&
                        fabs(contourArea(Mat(approx))) > 1000 &&
                        isContourConvex(Mat(approx)))
                {
                        double maxCosine = 0;

                        for (int j = 2; j < 5; j++)
                        {
                                double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                                maxCosine = MAX(maxCosine, cosine);
                        }

                        if (maxCosine < 0.3)
						{
                                squares.push_back(approx);
								return true;
						}
                }
        }
    }
	return false;
}

void findLargestSquare(std::vector<std::vector<cv::Point> >& squares)
{
	if(!squares.empty())
	{
		vector<vector<Point> > largestSquares;
		int max_width = 0;
		int max_height = 0;
		vector<vector<Point> >::iterator max;

		for(vector<vector<Point> >::iterator i = squares.begin();i < squares.end(); ++i)
		{
			// Convert a set of 4 unordered Points into a meaningful cv::Rect structure.
			Rect rectangle = boundingRect(Mat(*i));

			// Store the index position of the biggest square found
			if ((rectangle.width >= max_width) && (rectangle.height >= max_height))
			{
				max_width = rectangle.width;
				max_height = rectangle.height;
				max = i;
			}
		}
		largestSquares.push_back(*max);
		squares.clear();
		squares = largestSquares;

		sort(squares[0].begin(),squares[0].end(),sortPoint);
		cout << "(" << squares[0][0].x << "," << squares[0][0].y << "),"
		<< "(" << squares[0][1].x << "," << squares[0][1].y << "),"
		<< "(" << squares[0][2].x << "," << squares[0][2].y << "),"
		<< "(" << squares[0][3].x << "," << squares[0][3].y << ")," << endl;
	}
}

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle(Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}