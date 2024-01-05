#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
#include <Windows.h>
#include <wtypes.h>
#include <cstdio>
#include <cstdlib>
#include <thread>

using namespace cv;
using namespace std;

// All variables are declared global.

Mat img, imgHSV, mask, convert, blurr, canny, kernal, edge, out, UI;
Mat canvas(500, 650, CV_8UC3, Scalar(255, 255, 255));
Rect Wincord;
RECT Res, rect;
HWND wH;
int winx, winy, camid, eraser = 0, area, clrflag = 0, i;
float expox, expoy;
vector<vector<Point>> contours;
vector<vector<Point>> contoursp;
VideoCapture cam;
Point cord;

class colors {
public:
	int flag = 1;
	Scalar val;
	Scalar clr(int x, int y, int z) {
		Scalar temp(x, y, z);
		return temp;
	}
}red, blue, green, black, yellow, purple;

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
			expox = (winx / 650.0) + .07;
			expoy = (winy / 540.0) + .25;
			SetCursorPos(-(cord.x - 650) * expox, cord.y * expoy);
			if (!(cord.y > 450)) {
				for (int i = 0; i < 3; i++) {
					//centre
					circle(canvas, Point(-(cord.x - 650), cord.y), 4, Scalar(0, 0, 0), FILLED, 1000);
				}

			}
		}
	}
}

// Not in use but good to have it, below function returns the resolution of the screen.
// Update : Function still is bugged. Will try to fix and implement it.
// Update : Fixed and implemented.
void Getres(int& x, int& y) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	winx = desktop.right;
	winy = desktop.bottom;
}


void Eraser() {
	if (eraser == 0) {
		eraser = 1;
		rectangle(canvas, Point(0, 475), Point(140, 500), Scalar(255, 255, 255), FILLED, 10);
		putText(canvas, "Eraser enabled", Point(0, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	}
	else {
		eraser = 0;
		rectangle(canvas, Point(0, 475), Point(140, 500), Scalar(255, 255, 255), FILLED, 10);
		putText(canvas, "Eraser disabled", Point(0, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	}
}

void newCanvas() {
	rectangle(canvas, Point(0, 0), Point(650, 475), Scalar(255, 255, 255), FILLED, 10);
}

void colours() {
	clrflag = 1;
	red.val = red.clr(0, 0, 255);
	blue.val = blue.clr(255, 0, 0);
	green.val = green.clr(0, 255, 0);
	black.val = black.clr(0, 0, 0);
	yellow.val = yellow.clr(0, 255, 229);
	purple.val = purple.clr(255, 0, 255);
	rectangle(canvas, Point(250, 475), Point(650, 500), Scalar(255, 255, 255), FILLED, 10);
	putText(canvas, "Select : ", Point(250, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	Sleep(1);
	putText(canvas, "Red ", Point(320, 490), FONT_HERSHEY_DUPLEX, .5, red.val, 1, 20);
	Sleep(1);
	putText(canvas, "Green ", Point(360, 490), FONT_HERSHEY_DUPLEX, .5, green.val, 1, 20);
	Sleep(1);
	putText(canvas, "Blue", Point(420, 490), FONT_HERSHEY_DUPLEX, .5, blue.val, 1, 20);
	Sleep(1);
	putText(canvas, "Purple", Point(460, 490), FONT_HERSHEY_DUPLEX, .5, purple.val, 1, 20);
	Sleep(1);
	putText(canvas, "Yellow", Point(520, 490), FONT_HERSHEY_DUPLEX, .5, yellow.val, 1, 20);
	Sleep(1);
	putText(canvas, "Black", Point(580, 490), FONT_HERSHEY_DUPLEX, .5, black.val, 1, 20);
}


void Drawpointer(Mat edge, Mat canvas) {
	vector<Vec4i> hierarchy;
	Point cord;
	findContours(edge, contoursp, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contoursp.size());
	vector<Rect> boundRect(contoursp.size());
	for (int i = 0; i < contoursp.size(); i++) {
		area = 0;
		area = contourArea(contoursp[i]);
		if (area > 10) {
			float peri = arcLength(contoursp[i], true);
			approxPolyDP(contoursp[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]);
			cord.x = boundRect[i].x + boundRect[i].width / 2;
			cord.y = boundRect[i].y;
			expox = (winx / 650.0) + .07;
			expoy = (winy / 540.0) + .25;
			SetCursorPos(-(cord.x - 650) * expox, cord.y * expoy);
			//cout << -(cord.x - 650) * expox << "," << cord.y * expoy << endl;
			if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox < (51 * expox)) {
				cout << "Eraser";
				Sleep(2);
				Eraser();
			}
			else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (142 * expox) && -(cord.x - 650) * expox < (230 * expox)) {
				cout << "New Canvas";
				Sleep(2);
				newCanvas();
			}
			else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (248 * expox) && -(cord.x - 650) * expox < (290 * expox)) {
				cout << "Color";
				Sleep(2);
				colours();
			}
			else if (clrflag && !(eraser)) {
				if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (313 * expox) && -(cord.x - 650) * expox < (334 * expox)) {
					cout << "Red";
					green.flag = 0;
					blue.flag = 0;
					black.flag = 0;
					purple.flag = 0;
					yellow.flag = 0;
					Sleep(1);
					if (!(red.flag))
						red.flag = 1;
					else
						red.flag = 0;
				}
				else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (350* expox) && -(cord.x - 650) * expox < (387 * expox)) {
					cout << "Green";
					red.flag = 0;
					blue.flag = 0;
					black.flag = 0;
					purple.flag = 0;
					yellow.flag = 0;
					Sleep(1);
					if (!(green.flag))
						green.flag = 1;
					else
						green.flag = 0;
				}
				else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (410 * expox) && -(cord.x - 650) * expox < (437 * expox)) {
					cout << "Blue";
					green.flag = 0;
					red.flag = 0;
					black.flag = 0;
					purple.flag = 0;
					yellow.flag = 0;
					Sleep(1);
					if (!(blue.flag))
						blue.flag = 1;
					else
						blue.flag = 0;
				}
				else if (cord.y * expoy > (440 * expoy) && -(cord.x - 650) * expox > (447 * expox) && -(cord.x - 650) * expox < (488 * expox)) {
					cout << "Purple";
					green.flag = 0;
					blue.flag = 0;
					black.flag = 0;
					red.flag = 0;
					yellow.flag = 0;
					Sleep(1);
					if (!(purple.flag))
						purple.flag = 1;
					else
						purple.flag = 0;
				}
				else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (506 * expox) && -(cord.x - 650) * expox < (552 * expox)) {
					cout << "Yellow";
					green.flag = 0;
					blue.flag = 0;
					black.flag = 0;
					purple.flag = 0;
					red.flag = 0;
					Sleep(1);
					if (!(yellow.flag))
						yellow.flag = 1;
					else
						yellow.flag = 0;
				}
				else if (cord.y * expoy > (443 * expoy) && -(cord.x - 650) * expox > (562 * expox) && -(cord.x - 650) * expox < (60 * expox)) {
					cout << "Black";
					green.flag = 0;
					blue.flag = 0;
					red.flag = 0;
					purple.flag = 0;
					yellow.flag = 0;
					Sleep(1);
					if (!(black.flag))
						black.flag = 1;
					else
						black.flag = 0;

				}
			}
		}
	}
}

/*
void pointer() {
	while (true) {
		//freeCursor("canvas"); -> Obsolete
		cam.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		//inRange(imgHSV, Scalar(106, 126, 89), Scalar(124, 213, 149), mask);
		inRange(imgHSV, Scalar(0, 0, 244), Scalar(179, 255, 255), mask);
		//GaussianBlur(mask, blurr, Size(7, 7), 5, 0);
		//Canny(blurr, canny, 10, 10);
		//kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		//dilate(mask, edge, kernal);
		Drawpointer(mask, canvas);
		if (contoursp.size() == 0)
			return;
		imshow("canvas", canvas);

		waitKey(1);
	}
}*/


int main() {
	//*** Commmeted out some unneccessary code which slowed the entire program.
	cout << "Please enter camera id : ";
	cin >> camid;
	if (!(cam.open(camid))) {
		cout << "\n******Camera id not found.******\n";
		exit(0);
	}
	cam.open(camid);
	Getres(winx, winy);
	namedWindow("canvas", (winx, winy));
	Wincord = getWindowImageRect("canvas");
	putText(canvas, "Eraser disabled", Point(0, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	putText(canvas, "New Canvas", Point(140, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	putText(canvas, "Select Color", Point(250, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);

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
		//Draw(mask, canvas);
		//if (contours.size() == 0) {
		//pointer();
		Drawpointer(mask, canvas);
		//}
		imshow("canvas", canvas);
		waitKey(1);
	}
	return 0;
}