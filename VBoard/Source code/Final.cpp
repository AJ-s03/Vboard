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
int winx, winy, camid, eraser = 0, area, clrflag = 0;
vector<vector<Point>> contours;
vector<vector<Point>> contoursp;
VideoCapture cam;
Point cord;

// Class for color selector consisting flag and Scalar object of specified color.

class colors {
public:
	int flag = 1;
	Scalar val;
	Scalar clr(int x, int y, int z) {
		Scalar temp(x, y, z);
		return temp;
	}
}red, blue, green, black, yellow, purple;

// Not in use but good to have it, below function returns the resolution of the screen.

void Getres(int& x, int& y) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	winx = desktop.right;
	winy = desktop.bottom;
}

// Funtion for disabling and enabling eraser.

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

// Funtion for new canvas.

void newCanvas() {
	rectangle(canvas, Point(0, 0), Point(650, 475), Scalar(255, 255, 255), FILLED, 10);
}

// Function for selecting colors.

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

//Pointer check function was meant to be shared among pointer and draw funtions. It checks the coordinates and excutes the suitable statement when true.

void pointercheck() {
	if (cord.y > 470 && -(cord.x - 650) < 130) {
		Sleep(1);
		Eraser();
	}
	else if (cord.y > 470 && -(cord.x - 650) > 140 && -(cord.x - 650) < 250) {
		Sleep(1);
		newCanvas();
	}
	else if (cord.y > 470 && -(cord.x - 650) > 250 && -(cord.x - 650) < 320) {
		Sleep(1);
		colours();
	}
	else if (clrflag && !(eraser)) {
		if (cord.y > 470 && -(cord.x - 650) > 310 && -(cord.x - 650) < 350) {
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
		else if (cord.y > 470 && -(cord.x - 650) > 360 && -(cord.x - 650) < 410) {
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
		else if (cord.y > 470 && -(cord.x - 650) > 420 && -(cord.x - 650) < 450) {
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
		else if (cord.y > 470 && -(cord.x - 650) > 460 && -(cord.x - 650) < 510) {
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
		else if (cord.y > 470 && -(cord.x - 650) > 520 && -(cord.x - 650) < 570) {
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
		else if (cord.y > 470 && -(cord.x - 650) > 580 && -(cord.x - 650) < 620) {
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

// Funtion used to detect object of specific color and to draw at the coordinates wherever the object is located.

void Draw(Mat edge, Mat img, Mat canvas) {
	vector<Vec4i> hierarchy;
	findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		area = 0;
		area = contourArea(contours[i]);
		if (area > 10) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]);
			cord.x = boundRect[i].x + boundRect[i].width / 2;
			cord.y = boundRect[i].y;
			SetCursorPos((-(cord.x - 650) + Res.left), cord.y + Res.top);
			if (!(cord.y > 450)) {
				if (!(eraser)) {
					if (red.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, red.val, FILLED, 20);
					else if (green.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, green.val, FILLED, 20);
					else if (blue.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, blue.val, FILLED, 20);
					else if (black.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, black.val, FILLED, 20);
					else if (yellow.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, yellow.val, FILLED, 20);
					else if (purple.flag)
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, purple.val, FILLED, 20);
					else
						for (int i = 0; i < 6; i++)
							circle(canvas, Point(-(cord.x - 650), cord.y), 10, black.val, FILLED, 20);
				}
				else
					for (int i = 0; i < 6; i++)
						circle(canvas, Point(-(cord.x - 650), cord.y), 20, Scalar(255, 255, 255), FILLED, 20);
			}
			pointercheck();
		}
	}
}

// Funtion for pointer.

void Drawpointer(Mat edge, Mat img, Mat canvas) {
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
			SetCursorPos((-(cord.x - 650) + Res.left), cord.y + Res.top);
			if (cord.y > 470 && -(cord.x - 650) < 130) {
				Sleep(1);
				Eraser();
			}
			else if (cord.y > 470 && -(cord.x - 650) > 140 && -(cord.x - 650) < 250) {
				Sleep(1);
				newCanvas();
			}
			else if (cord.y > 470 && -(cord.x - 650) > 250 && -(cord.x - 650) < 320) {
				Sleep(1);
				colours();
			}
			else if (clrflag && !(eraser)) {
				if (cord.y > 470 && -(cord.x - 650) > 310 && -(cord.x - 650) < 350) {
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
				else if (cord.y > 470 && -(cord.x - 650) > 360 && -(cord.x - 650) < 410) {
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
				else if (cord.y > 470 && -(cord.x - 650) > 420 && -(cord.x - 650) < 450) {
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
				else if (cord.y > 470 && -(cord.x - 650) > 460 && -(cord.x - 650) < 510) {
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
				else if (cord.y > 470 && -(cord.x - 650) > 520 && -(cord.x - 650) < 570) {
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
				else if (cord.y > 470 && -(cord.x - 650) > 580 && -(cord.x - 650) < 620) {
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

// Funtion used to to free the cursor (check later).

void freeCursor(const char* name) {
	wH = (HWND)cvGetWindowHandle(name);
	GetWindowRect(wH, &rect);
	Res.left = rect.left;
	Res.top = rect.top;
	Res.right = rect.right;
	Res.bottom = rect.bottom;
}

// Funtion for detecting pointer object.

void pointer() {
	while (true) {
		freeCursor("canvas");
		cam.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(106, 126, 89), Scalar(124, 213, 149), mask);
		GaussianBlur(mask, blurr, Size(7, 7), 5, 0);
		Canny(blurr, canny, 10, 10);
		kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(canny, edge, kernal);
		Drawpointer(edge, mask, canvas);
		if (contoursp.size() == 0)
			return;
		imshow("canvas", canvas);

		waitKey(1);
	}
}

// Funtion to set the bounds of cursor when drawing.

void setCursor(const char* name) {
	wH = (HWND)cvGetWindowHandle(name);
	GetWindowRect(wH, &rect);
	Res.left = rect.left;
	Res.top = rect.top;
	Res.right = rect.right;
	Res.bottom = rect.bottom;
}


int main() {
	cout << "Please enter camera id : ";
	cin >> camid;
	if (!(cam.open(camid))) {
		cout << "\n******Camera id not found.******\n";
		exit(0);
	}
	cam.open(camid);
	namedWindow("canvas", WINDOW_FULLSCREEN);
	Wincord = getWindowImageRect("canvas");
	Getres(winx, winy);
	putText(canvas, "Eraser disabled", Point(0, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	putText(canvas, "New Canvas", Point(140, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	putText(canvas, "Select Color", Point(250, 490), FONT_HERSHEY_DUPLEX, .5, Scalar(0, 0, 0), 1, 20);
	while (true) {
		cam.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(27, 49, 145), Scalar(80, 191, 251), mask);
		GaussianBlur(mask, blurr, Size(7, 7), 5, 0);
		Canny(blurr, canny, 10, 10);
		kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(canny, edge, kernal);
		if (contours.size() > 0)
			setCursor("canvas");
		Draw(edge, mask, canvas);
		if (contours.size() == 0) {
			pointer();
		}
		imshow("canvas", canvas);
		waitKey(1);
	}
	return 0;
}

