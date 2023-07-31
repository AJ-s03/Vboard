#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	string path = "Resources\\gruntface.jpg";
	Mat img = imread(path);
	Point2f src[4] = {{0,0},{600,0},{0,622},{600,622}};
	Point2f des[4] = {{ 400,400 }, { 600,400 }, { 600,600 }, { 800,600}};
	
	Mat matrix, imgwarp;
	matrix = getPerspectiveTransform(src, des);
	warpPerspective(img, imgwarp, matrix,Point(900,900));
	for (int i = 0; i < 4; i++)
	{
		circle(img, des[i], 10, Scalar(0, 255, 0), FILLED, 20);

	}
	imshow("image", imgwarp);
	waitKey(0);
	return 0;
}