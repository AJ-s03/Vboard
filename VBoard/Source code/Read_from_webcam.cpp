#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	VideoCapture cap(0);
	Mat img;
	while (true) {
		cap.read(img);
		imshow("Skyrim", img);
		waitKey(1);
	}
	return 0;

}