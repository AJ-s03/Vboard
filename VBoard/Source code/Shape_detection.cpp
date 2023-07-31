#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void contours(Mat edge, Mat img) {
	
	vector<vector<Point>> contours;
	//vector<vector<Point>> conPoly(contours.size());
	vector<Vec4i> hierarchy;
	findContours(edge, contours, hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(0, 0, 0), FILLED, 20);
	/*for (int i = 0; i < contours.size() ; i++){
		int area = contourArea(contours[i]);
		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(0, 0, 0), 10, 20);
		}
	}*/
}

int main() {
	string path = "Resources\\shapes.png";
	Mat img = imread(path);
	Mat convert, blur, canny, kernal, edge, out;
	cvtColor(img, convert, COLOR_BGR2GRAY);
	GaussianBlur(img, blur, Size(7, 7), 5, 0);
	Canny(blur, canny, 10, 10);
	kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(canny, edge , kernal);

	contours(edge, img);

	imshow("image edge", img);
	waitKey(0);
	return 0;
}