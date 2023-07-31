#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main() {
	string path = "Resources\\chillingnaut.jpg";
	Mat img = imread(path);
	Mat imgHSV,mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("Trackbars",(800, 200));
	createTrackbar("Hue min", "Trackbars", &hmin, 179);
	createTrackbar("Hue max", "Trackbars", &hmax, 179);
	createTrackbar("Saturation min", "Trackbars", &smin, 255);
	createTrackbar("Saturation max", "Trackbars", &smax, 255);
	createTrackbar("Value min", "Trackbars", &vmin, 255);
	createTrackbar("Value max", "Trackbars", &vmax, 255);
	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("image", img);
		imshow("image HSV", imgHSV);
		imshow("image mask", mask);
		waitKey(1);
	}
	return 0;
}