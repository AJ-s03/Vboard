#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;


int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
Mat img, imgHSV, mask, convert, blurr, canny, kernal, edge, out;
Mat canvas(500, 650, CV_8UC3, Scalar(255, 255, 255));

void contours(Mat edge, Mat img, Mat canvas) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Point cord;
	findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(0, 255, 0), 10, 20);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size() ; i++){
		int area = contourArea(contours[i]);
		//cout << area << endl;
		if (area > 1000) {
				//drawContours(img, contours, -1, Scalar(255, 255, 255), 10, 20);
				float peri = arcLength(contours[i], true);
				approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
				boundRect[i] = boundingRect(conPoly[i]);
				cord.x = boundRect[i].x + boundRect[i].width / 2;
				cord.y = boundRect[i].y;
				printf("The object is at : (%d,%d)\n",cord.x, cord.y);
				circle(canvas, Point(cord.x, cord.y), 10, Scalar(0, 255, 0), FILLED, 10);
		}
	}
}

int main() {
	VideoCapture cam(0);
	string path = "Resources\\canvas.png";
	canvas = imread(path);
	namedWindow("Test_canvas",WINDOW_AUTOSIZE);
	while (true) {
		cam.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(23, 109, 152), Scalar(38, 254, 255), mask);
		//cvtColor(mask, convert, COLOR_BGR2GRAY);
		GaussianBlur(mask, blurr, Size(7, 7), 5, 0);
		Canny(blurr, canny, 10, 10);
		kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(canny, edge, kernal);
		contours(edge, mask, canvas);
		imshow("Test_Canvas", canvas);
		waitKey(1);
	}
	return 0;
}
