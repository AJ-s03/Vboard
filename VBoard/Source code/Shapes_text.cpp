#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat img(500,650, CV_8UC3, Scalar(255,255,255));
	circle(img, Point(250, 250), 200, Scalar(0, 0, 0), FILLED, 20);
	rectangle(img,Point(130, 226), Point(382, 286), Scalar(255, 255, 255), 3);
	line(img, Point(250, 0), Point(250, 500), Scalar(255, 255, 255), 3);
	putText(img, "OpenComputerVision", Point(0, 100), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 255, 0), 2, 10);
	imshow("image", img);
	waitKey(0);
	return 0;
}