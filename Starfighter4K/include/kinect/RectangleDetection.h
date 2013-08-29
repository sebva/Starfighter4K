#ifndef RECTANGLE_DETECTION_H
#define RECTANGLE_DETECTION_H

#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <array>

class RectangleDetection
{
public:
	RectangleDetection(int _thresh = 50, int _N = 11);
	void addImage(const cv::Mat& image);
	std::array<cv::Point, 4> getPoints();
	size_t getSizeImages() const {return images.size();}

private:
	std::vector<cv::Mat> images;
	std::vector<std::vector<std::vector<cv::Point>>> points;
	int thresh;
	int N;
};

double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0 );
bool findSquares(const cv::Mat& image, std::vector<std::vector<cv::Point> >& squares, int thresh, int N);
void findLargestSquare(std::vector<std::vector<cv::Point> >& squares);

#endif