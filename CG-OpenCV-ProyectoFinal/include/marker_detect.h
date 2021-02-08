
#ifndef MARKER_DETECT_H
#define MARKER_DETECT_H

class marker
{
private:
	int size;
	cv::Mat calib_frame;
	std::vector<cv::Point3f> object_points;
	std::vector<cv::Point2f> image_points;
	cv::Mat cameraMatrix,cameraDistortion;
    cv::Ptr<cv::aruco::Dictionary> dictionary;

public:
	cv::Mat  rvecs, tvecs;
	bool  detect_flag;
	marker(char**, cv::Mat&, cv::Mat&);
	bool marker_detect(cv::Mat);


};

#endif
