#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	String path = "Resources\\image.jpg";
	Mat img = imread(path);
	imshow("Image", img);
	waitKey(0);
	return 0;
}