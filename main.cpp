#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <math.h> 
#include <time.h> 
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	vector<vector<Point3f>> objectPoints;

	vector<vector<Point2f>> imagePoints;
	Size imageSize;
	std::ifstream worldPoints("E:/PROGRAM/Project_PhD/NDI/Solution/PickedFiducialList_normalized_12.txt");
	std::string line;
	double i, x, y, z, t;
	vector<Point3f> objectPointsSingle;
	
	while (!worldPoints.eof())
	{
		getline(worldPoints, line);
		std::istringstream iss(line);
		iss >> i >> x >> y >> z >> t;
		//std::cout << x << " " << y << " " << z << endl;
		objectPointsSingle.push_back(Point3f(x, y, z));
		
	}
	
	

	string baseDirectory = "E:/PROGRAM/Project_PhD/NDI/Solution/ImagePoints_post_no_flip/CalibrateData/";

	int numImages = 163;
	srand(time(NULL));
	

	

	for (int i = 0; i < 56; i++)
	{
		//int randIndex = rand() % numImages + 1; // range 1 to 163
		int calibrateIndex = i * 3 + 1;
		std::cout << calibrateIndex << std::endl;
		string randomIndex_s = std::to_string(calibrateIndex);
		//string index = std::to_string(i+1);
		string fileName = baseDirectory + "imagePoints" + randomIndex_s + ".txt";
		//string fileName = baseDirectory + "calibrationData.txt";
		std::ifstream imagePointsReader(fileName);
		std::string line1;
		double x1, y1;
		vector<Point2f> imagePointsSingle;
		
		while (!imagePointsReader.eof())
		{
			
			
				getline(imagePointsReader, line1);
				std::istringstream iss1(line1);
				iss1 >> x1 >> y1;
				//std::cout << x << " " << y << " " << z << endl;
				imagePointsSingle.push_back(Point2f(x1, y1));

		}
		imagePointsSingle.pop_back();
		imagePoints.push_back(imagePointsSingle);
		objectPoints.push_back(objectPointsSingle);
		//std::cout << imagePoints[i] << std::endl;
	}
	std::cout << size(objectPoints) << std::endl;
	std::cout << size(imagePoints) << std::endl;

	imageSize.width = 1024;
	imageSize.height = 1024;
	int iFixedPoint = -1;
	Mat cameraMatrix;
	Mat distCoeffs;
	vector<Mat> rvecs;
	vector<Mat> tvecs;
	vector<float> reprojErrs;
	double totalAvgErr;
	vector<Point3f> newObjPoints;
	totalAvgErr = calibrateCameraRO(objectPoints, imagePoints, imageSize, iFixedPoint, cameraMatrix, distCoeffs, rvecs, tvecs, newObjPoints, (CALIB_FIX_K1 + CALIB_FIX_K2 + CALIB_FIX_K3));

	std::cout << cameraMatrix << std::endl;
	std::cout << distCoeffs << std::endl;
	return 0;
}