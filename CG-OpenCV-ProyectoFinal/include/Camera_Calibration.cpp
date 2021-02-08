/*
 * Camera_Calibration.cpp
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
#include "Camera_Calibration.h"
using namespace std;
using namespace cv;



Camera_Calibration::Camera_Calibration(){
	aspectRatio = 1;
	dictionaryId=16;
}

void Camera_Calibration::Calibrate() {

    VideoCapture inputVideo;
    int waitTime;

    inputVideo.open(1);
    waitTime = 10;

    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
    Ptr<aruco::GridBoard> gridboard =aruco::GridBoard::create(3, 2, 0.055f, 0.013, dictionary);
    Ptr<aruco::Board> board = gridboard.staticCast<aruco::Board>();
    // create board object


    // collected frames for calibration
    vector< vector< vector< cv::Point2f > > > allCorners;
    vector< vector< int > > allIds;
    Size imgSize;
    Mat image, imageCopy;
    while(inputVideo.grab()) {

        inputVideo.retrieve(image);

        vector< int > ids;
        vector< vector< Point2f > > corners, rejected;

        // detect markers
        aruco::detectMarkers(image, dictionary, corners, ids,detectorParams, rejected);
        aruco::refineDetectedMarkers(image, board, corners, ids, rejected);

        // draw results
        image.copyTo(imageCopy);
        if(ids.size() > 0) aruco::drawDetectedMarkers(imageCopy, corners, ids);
        putText(imageCopy, "Press 'c' to add current frame. 'ESC' to finish and calibrate",
                Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);

        imshow("out", imageCopy);
        char key = (char)waitKey(waitTime);
        if(key == 27) break;
        if(key == 'c' && ids.size() > 0) {
            cout << "Frame captured" << endl;
            allCorners.push_back(corners);
            allIds.push_back(ids);
            imgSize = image.size();
        }
    }
    inputVideo.release();

    if(allIds.size() < 1) {
        cerr << "Not enough captures for calibration" << endl;
    }


    double repError;

    int calibration_flags=0;
    cameraMatrix = Mat::eye(3, 3, CV_64F);
    cameraMatrix.at< double >(0, 0) = aspectRatio;
    distCoeffs=Mat(5,1,CV_64F);

    // prepare data for calibration
    vector< vector< Point2f > > allCornersConcatenated;
    vector< int > allIdsConcatenated;
    vector< int > markerCounterPerFrame;
    markerCounterPerFrame.resize(allCorners.size());
    for(unsigned int i = 0; i < allCorners.size(); i++) {
        markerCounterPerFrame.push_back((int)allCorners[i].size());
        for(unsigned int j = 0; j < allCorners[i].size(); j++) {
            allCornersConcatenated.push_back(allCorners[i][j]);
            allIdsConcatenated.push_back(allIds[i][j]);
        }
    }
    // calibrate camera

    std::cerr <<cameraMatrix.size()<< endl;
    repError = aruco::calibrateCameraAruco(allCornersConcatenated, allIdsConcatenated, markerCounterPerFrame, board, imgSize, cameraMatrix,distCoeffs);


    //cout << "Rep Error: " << repError << endl;
}
