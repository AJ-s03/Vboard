#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
#include <Windows.h>
#include <wtypes.h>
#include <cstdio>
#include <cstdlib>

using namespace cv;
using namespace std;

// All variables are declared global.

Mat img, imgHSV, mask, convert, blurr, canny, kernal, edge, out;
Mat canvas(500, 650, CV_8UC3, Scalar(255, 255, 255));
Rect Wincord;
RECT Res, rect;
HWND wH;
int winx, winy, camid, eraser = 0, area, clrflag = 0, i;
vector<vector<Point>> contours;
vector<vector<Point>> contoursp;
VideoCapture cam;
Point cord;

void Draw(Mat edge, Mat canvas) {
	vector<Vec4i> hierarchy;
	findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		area = 0;
		area = contourArea(contours[i]);
		if (area > 500) {
			//cout << "(x,y) : " << "(" << winx << "," << winy << ")" << endl;
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]);
			cord.x = boundRect[i].x + boundRect[i].width / 2;
			cord.y = boundRect[i].y;
			SetCursorPos((-(cord.x - 650) + Res.left), cord.y + Res.top);
			if (!(cord.y > 450)) {
				for (int i = 0; i < 3; i++){
					//centre
					circle(canvas, Point(-(cord.x - 650), cord.y), 5, Scalar(0, 0, 0), FILLED, 1000);
					//forward
					
					circle(canvas, Point(-(cord.x - 650) + i, cord.y), 5, Scalar(0, 0, 0), FILLED, 1000);
					circle(canvas, Point(-(cord.x - 650), cord.y + i), 5, Scalar(0, 0, 0), FILLED, 1000);
					circle(canvas, Point(-(cord.x - 650) + i, cord.y + i), 5, Scalar(0, 0, 0), FILLED, 1000);
					//backward
					
					circle(canvas, Point(-(cord.x - 650) - i, cord.y), 5, Scalar(0, 0, 0), FILLED, 1000);
					circle(canvas, Point(-(cord.x - 650), cord.y - i), 5, Scalar(0, 0, 0), FILLED, 1000);
					circle(canvas, Point(-(cord.x - 650) - i, cord.y - i), 5, Scalar(0, 0, 0), FILLED, 1000);
				}
					
			}
		}
	}

}
	int main(){
		//*** Commmeted out some unneccessary code which slowed the entire program.
		cout << "Please enter camera id : ";
		cin >> camid;
		if (!(cam.open(camid))) {
			cout << "\n******Camera id not found.******\n";
			exit(0);
		}
		cam.open(camid);
		namedWindow("canvas", WINDOW_FULLSCREEN);
		Wincord = getWindowImageRect("canvas");
		//Getres(winx, winy);
		//putText(canvas, "Eraser disabled", Point(0, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
		//putText(canvas, "New Canvas", Point(140, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
		//putText(canvas, "Select Color", Point(250, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
		while (true) {
			cam.read(img);
			//imshow("img", img);
			cvtColor(img, imgHSV, COLOR_BGR2HSV);
			//imshow("imgHSV", imgHSV);
			inRange(imgHSV, Scalar(0, 0, 244), Scalar(179, 255, 255), mask);
			//imshow("mask", mask);
			//GaussianBlur(mask, blurr, Size(7, 7), 5, 0);
			//imshow("blurr", blurr);
			//Canny(blurr, canny, 10, 10);
			//imshow("canny", canny);
			//kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
			//dilate(mask, edge, kernal);
			//imshow("edge", edge);
			//if (contours.size() > 0)
				//setCursor("canvas");
			Draw(mask, canvas);
			//if (contours.size() == 0) {
				//pointer();
			//}
			imshow("canvas", canvas);
			waitKey(1);
		}
		return 0;
	}