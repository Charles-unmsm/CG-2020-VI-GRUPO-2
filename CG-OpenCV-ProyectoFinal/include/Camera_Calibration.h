/*
 * Camera_Calibration.h
 *
 *  Created on: 7 feb. 2021
 *      Author: Hiroshi
 */

#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
using namespace cv;

class Camera_Calibration{
public:
Mat cameraMatrix, distCoeffs;
Mat rvecs, tvecs;
int dictionaryId;
float aspectRatio;
void Calibrate();
Camera_Calibration();
};



