#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	String path = "Resources\\image.jpg";
	Mat img = imread(path);
	Mat convert, blur, edge, dilation, kernal, erosion;
	cvtColor(img, convert, COLOR_BGR2GRAY);
	GaussianBlur(img, blur, Size(7, 7), 5, 0);
	Canny(blur, edge, 10, 10);
	waitKey(0);
	return 0;
}