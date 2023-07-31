#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, convert, blurr, canny, kernal, edge, out;
void draw() {
	circle(img, Point(250, 250), 200, Scalar(0, 0, 0), FILLED, 20);
}



int main() {
	VideoCapture cam(0);
	while (true) {
		cam.read(img);
		draw();
		/*
		cvtColor(img, convert, COLOR_BGR2GRAY);
		GaussianBlur(img, blurr, Size(7, 7), 5, 0);
		Canny(blurr, canny, 10, 10);
		kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(canny, edge, kernal);
		*/
		namedWindow("Webcam", WINDOW_FREERATIO);
		imshow("Webcam", img);
		waitKey(1);
	}
	return 0;

}