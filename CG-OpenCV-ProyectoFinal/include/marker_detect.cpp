/*****************************************************************************
 * Author : Ram
 * Date : 14/May/2018
 * Email : ramkalath@gmail.com
 * Breif Description : implements aruco marker detection
 * Detailed Description : I was too lazy to parse out the marker id's and automatically generate the object points and image points. I hardcoded it :P
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp> // include the aruco import
#include <strings.h>
#include <vector>
#include "../include/Camera_Calibration.h"
#include "marker_detect.h"
using namespace cv;
using namespace std;

//********************************************************************
// creates a marker class with a constructor initializing several variables
// to detect a marker the constructor has a prototype marker(char** args, cv::Mat& intrinsic_matrix, cv::Mat& distortion_coefficients);
// args has the format ()
// the next two cv::Mat& and cv::Mat& takes in the pointer for intrinsic_matrix and distortion_coefficients. Aruco reads the intrinsic_matrix and the distortion_coefficients from an xml file. 
// the marker_detect(cv::Mat frame) takes in a webcam grabbed frame for marker detection. 
// rvecs and tvecs are declared under public to be accessed in main for passing to the object overlay method.

/************************* dictionary:
 * DICT_4X4_50=0
 * DICT_4X4_100=1
 * DICT_4X4_250=2
 * DICT_4X4_1000=3
 * DICT_5X5_50=4
 * DICT_5X5_100=5
 * DICT_5X5_250=6
 * DICT_5X5_1000=7
 * DICT_6X6_50=8
 * DICT_6X6_100=9
 * DICT_6X6_250=10
 * DICT_6X6_1000=11
 * DICT_7X7_50=12
 * DICT_7X7_100=13
 * DICT_7X7_250=14
 * DICT_7X7_1000=15
 * DICT_ARUCO_ORIGINAL = 16
 *************************/
/*
class marker
{
private:
	int size;
	cv::Mat calib_frame;
	vector<cv::Point3f> object_points;
	vector<cv::Point2f> image_points;
	cv::Mat cameraMatrix,cameraDistortion;
    cv::Ptr<cv::aruco::Dictionary> dictionary;

public:
	cv::Mat  rvecs, tvecs;
	bool  detect_flag;
	marker(char**, cv::Mat&, cv::Mat&);
	bool marker_detect(cv::Mat);


};
*/
// constructor 
marker::marker(char** argv, cv::Mat& intrinsic_matrix, cv::Mat& distortion_parameters)
{
	int dict_number = 16;
	//Camera_Calibration CC;
	//CC.Calibrate();
	float m[3][3] = {{1751.4028018776 ,0. ,1263.5},
			{0. ,1751.4028018776246 ,927.5}, {0., 0., 1.}};
	cameraMatrix= cv::Mat(3,3, CV_64F,m);
	float n[5][1]={1.3287735059062630e-01 ,-6.8376776294978103e-01, 0. ,0. ,8.1215478360827675e-01 };
	cameraDistortion=cv::Mat(5,1, CV_64F,n);
	cv::Mat rvecs=Mat::zeros(1,3,CV_64F);
	cv::Mat tvecs=Mat::zeros(1,3,CV_64F);
	detect_flag =false;
    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(dict_number));
    intrinsic_matrix=cameraMatrix;
    size=0;

}

// marker detection function which detects markers and gives out rvecs and tvecs
// there are a set of image and object points which aruco detects. The image points are detected and the dumped into a stack. Corresponding object points are dumped into a stack as well. 
// finally tvecs and rvecs are calibrated.
bool marker::marker_detect(cv::Mat frame)
{
		std::vector<int> ids;
	    std::vector<std::vector<cv::Point2f>> corners;
	    cv::aruco::detectMarkers(frame, dictionary, corners, ids);
		size = 0;
		detect_flag = false;
		object_points.clear();
		image_points.clear();
		size=ids.size();
		for (int i=0;i<size;i++)
		{	

			            std::vector<cv::Point> pts_dst;
			            pts_dst.push_back(corners[i][0]);
			            pts_dst.push_back(corners[i][1]);
			            pts_dst.push_back(corners[i][2]);
			            pts_dst.push_back(corners[i][3]);
			switch(ids.at(i))
			{		
  				case 227:
  				{	
 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
							three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
							four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);
							
						Point3f one_obj_pt(0, 0, 0),
								two_obj_pt(10, 0, 0),
								three_obj_pt(10, 10, 0),
								four_obj_pt(0, 10, 0);
					
					image_points.push_back(one_img_pt);
					image_points.push_back(two_img_pt);
					image_points.push_back(three_img_pt);
					image_points.push_back(four_img_pt);
					
					object_points.push_back(one_obj_pt);
					object_points.push_back(two_obj_pt);
					object_points.push_back(three_obj_pt);
					object_points.push_back(four_obj_pt);
					//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
					break;
 				}
  				case 1008:
  				  				{
  				 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
  				 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
  											three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
  											four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);

  									Point3f one_obj_pt(0, 0, 0),
  											two_obj_pt(10, 0, 0),
  											three_obj_pt(10, 10, 0),
  											four_obj_pt(0, 10, 0);

  									image_points.push_back(one_img_pt);
  									image_points.push_back(two_img_pt);
  									image_points.push_back(three_img_pt);
  									image_points.push_back(four_img_pt);

  									object_points.push_back(one_obj_pt);
  									object_points.push_back(two_obj_pt);
  									object_points.push_back(three_obj_pt);
  									object_points.push_back(four_obj_pt);
  									//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
  									break;
  				 				}
  				case 631:
  				  				{
  				 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
  				 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
  											three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
  											four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);

  									Point3f one_obj_pt(0, 0, 0),
  											two_obj_pt(10, 0, 0),
  											three_obj_pt(10, 10, 0),
  											four_obj_pt(0, 10, 0);

  									image_points.push_back(one_img_pt);
  									image_points.push_back(two_img_pt);
  									image_points.push_back(three_img_pt);
  									image_points.push_back(four_img_pt);

  									object_points.push_back(one_obj_pt);
  									object_points.push_back(two_obj_pt);
  									object_points.push_back(three_obj_pt);
  									object_points.push_back(four_obj_pt);
  									//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
  									break;
  				 				}
  				case 939:
  				  				{
  				 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
  				 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
  											three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
  											four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);

  									Point3f one_obj_pt(0, 0, 0),
  											two_obj_pt(10, 0, 0),
  											three_obj_pt(10, 10, 0),
  											four_obj_pt(0, 10, 0);

  									image_points.push_back(one_img_pt);
  									image_points.push_back(two_img_pt);
  									image_points.push_back(three_img_pt);
  									image_points.push_back(four_img_pt);

  									object_points.push_back(one_obj_pt);
  									object_points.push_back(two_obj_pt);
  									object_points.push_back(three_obj_pt);
  									object_points.push_back(four_obj_pt);
  									//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
  									break;
  				 				}

  				case 861:
  				  				{
  				 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
  				 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
  											three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
  											four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);

  									Point3f one_obj_pt(0, 0, 0),
  											two_obj_pt(10, 0, 0),
  											three_obj_pt(10, 10, 0),
  											four_obj_pt(0, 10, 0);

  									image_points.push_back(one_img_pt);
  									image_points.push_back(two_img_pt);
  									image_points.push_back(three_img_pt);
  									image_points.push_back(four_img_pt);

  									object_points.push_back(one_obj_pt);
  									object_points.push_back(two_obj_pt);
  									object_points.push_back(three_obj_pt);
  									object_points.push_back(four_obj_pt);
  									//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
  									break;
  				 				}
  				case 182:
  				  				{
  				 					Point2f one_img_pt(pts_dst.at(0).x, pts_dst.at(0).y),
  				 							two_img_pt(pts_dst.at(1).x, pts_dst.at(1).y),
  											three_img_pt(pts_dst.at(2).x, pts_dst.at(2).y),
  											four_img_pt(pts_dst.at(3).x, pts_dst.at(3).y);

  									Point3f one_obj_pt(0, 0, 0),
  											two_obj_pt(10, 0, 0),
  											three_obj_pt(10, 10, 0),
  											four_obj_pt(0, 10, 0);

  									image_points.push_back(one_img_pt);
  									image_points.push_back(two_img_pt);
  									image_points.push_back(three_img_pt);
  									image_points.push_back(four_img_pt);

  									object_points.push_back(one_obj_pt);
  									object_points.push_back(two_obj_pt);
  									object_points.push_back(three_obj_pt);
  									object_points.push_back(four_obj_pt);
  									//cout<<object_points<<"\n"<<image_points<<"\n\n\n\n";
  									break;
  				 				}


		}
			std::cerr << "Marcadores encontrados" << std::endl;

		}

		if (size > 1){
			detect_flag = true;

		}
		
		if(detect_flag){
			cv::solvePnP(object_points, image_points, cameraMatrix,cameraDistortion, rvecs, tvecs);
			std::cerr << "PNP realizado." << std::endl;
			std::cerr << rvecs << std::endl;
			std::cerr << tvecs << std::endl;
			std::cerr << detect_flag << std::endl;
			return true;
		}else{
			return false;
		}



}
 
