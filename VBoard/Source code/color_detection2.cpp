#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int Rmin = 0, Gmin = 0, Bmin = 0;
int Rmax = 255, Gmax = 255, Bmax = 255;

int main() {
	string path = "Resources\\chillingnaut.jpg";
	Mat img = imread(path);
	Mat imgRGB, mask;
	cvtColor(img, imgRGB, COLOR_BGR2RGB);
	namedWindow("Trackbars", (800, 200));
	createTrackbar("Red min", "Trackbars", &Rmin, 255);
	createTrackbar("Red max", "Trackbars", &Rmax, 255);
	createTrackbar("Green min", "Trackbars", &Gmin, 255);
	createTrackbar("Green max", "Trackbars", &Gmax, 255);
	createTrackbar("Blue min", "Trackbars", &Bmin, 255);
	createTrackbar("Blue max", "Trackbars", &Bmax, 255);
	while (true) {
		Scalar lower(Rmin, Gmin, Bmin);
		Scalar upper(Rmax, Gmax, Bmax);
		inRange(imgRGB, lower, upper, mask);
		imshow("image", img);
		imshow("image RGB", imgRGB);
		imshow("image mask", mask);
		waitKey(1);
	}
	return 0;
}