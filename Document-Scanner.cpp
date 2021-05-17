#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat imgOriginal, imgGray, imgCanny, imgBlur, imgDilate;
vector<Point> initialPoints, finalPoints;
float w = 420, h = 596;

Mat preProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	dilate(imgCanny, imgDilate, kernel);
	return (imgDilate);
}



vector<Point> getContours(Mat imgMask)
{

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> contourPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point> biggest;
	int maxArea = -10;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		if (area >= 1000)
		{
			cout << "ENTERED LOOP 1";
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			if (area > maxArea && contourPoly[i].size() == 4)
			{
				cout << "ENTERED LOOP 2";
				//drawContours(imgOriginal, contourPoly, i, Scalar(255, 0, 255), 3);
				maxArea = area;
				biggest = { contourPoly[i][0], contourPoly[i][1], contourPoly[i][2], contourPoly[i][3] };
			}


			//cout << contourPoly[i] << endl;
		}
	}
	return(biggest);
}




void drawPoints(vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 5, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 5);
	}
}

vector<Point> reOrder(vector<Point> points)
{
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

	return newPoints;
}



Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
	Point2f src[4] = { points[0], points[1], points[2], points[3] };
	Point2f dest[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	Mat inter = getPerspectiveTransform(src, dest);
	Mat imgWarp;
	warpPerspective(img, imgWarp, inter, Size(w, h));
	return(imgWarp);
}

void main()
{
	VideoCapture cap(0);
	Mat imgCrop, imgWarp, imgThreshold;

	string path = "Resources/two.jpg";
	imgOriginal = imread(path);

	//setting cropFactor, for clarity
	int cropFactor = 10;
	Rect roi(cropFactor, cropFactor, w - (2 * cropFactor), h - (2 * cropFactor));

	/*while (true)
	{
		cap.read(imgOriginal);*/


	//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	//Preprocessing
	imgThreshold = preProcessing(imgOriginal);


	//Getting contours - Biggest (A4 paper)
	initialPoints = getContours(imgThreshold);
	/*imshow("Image", imgOriginal);
	imshow("ImageThreshold", imgThreshold);*/

	//reordering
	finalPoints = reOrder(initialPoints);
	//drawPoints(finalPoints, Scalar(0, 0, 255));

	//warping image
	imgWarp = getWarp(imgOriginal, finalPoints, w, h);

	//cropping
	imgCrop = imgWarp(roi);

	imshow("Image", imgOriginal);
	imshow("ImageThreshold", imgThreshold);
	imshow("ImageWarp", imgWarp);
	imshow("ImageCropped", imgCrop);

	//	waitKey(1);
	//}




	waitKey(0);


}

