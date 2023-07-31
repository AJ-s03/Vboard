#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
void draw() {
	circle(img, Point(250, 250), 200, Scalar(0, 0, 0), FILLED, 20);
}

int main() {
	VideoCapture cap("Resources\\video.mp4");
	while (true) {
		cap.read(img);
		draw();
		imshow("Skyrim", img);
		waitKey(50);
	}
	return 0;
}