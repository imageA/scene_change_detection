#include "SceneChangeDetector.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

SceneChangeDetector::SceneChangeDetector(){
	
}

int SceneChangeDetector::doWork(cv::Mat& input){

	//if(omatInputGray_.cols != input.cols || omatInputGray_.rows != input.rows){
	if(omatInputGray_.empty()){
		omatInputGray_ = cv::ocl::oclMat(input.rows, input.cols, CV_8UC1);
	}
	if(omatInput_.empty()){
		omatInput_ = cv::ocl::oclMat(input.rows, input.cols, input.type());
	}

	if(matResult_.empty()){
		matResult_ = cv::Mat(input.rows, input.cols, CV_8UC1);
	}
	
	if(omatCornerHarris_.empty()) {
		//omatCornerHarris_ = cv::ocl::oclMat(input.rows, input.cols, CV_32FC1);
		omatCornerHarris_ = cv::ocl::oclMat(input.rows, input.cols, CV_8UC1);
	}

	//upload input frame
	omatInput_.upload(input); //WARNING : blocking call

	//process
	cv::ocl::cvtColor(omatInput_, omatInputGray_, CV_BGR2GRAY);
	
	//cv::ocl::equalizeHist(omatInputGray_, omatInputGray_);

	//cv::ocl::threshold(omatInputGray_, omatInputGray_, 200, 255, cv::THRESH_TRUNC);
	//cv::ocl::threshold(omatInputGray_, omatInputGray_, 150, 255, cv::THRESH_BINARY);
	cv::ocl::oclMat omat_dst_norm;

	
	///////https://gist.github.com/wzpan/8996603
	double minStrength, maxStrength;
	cv::ocl::cornerHarris(omatInputGray_, omatCornerHarris_, 3, 3, 0.1, cv::BORDER_DEFAULT);
	cv::ocl::minMaxLoc(omatCornerHarris_, &minStrength, &maxStrength);

	cv::ocl::oclMat omatDialted;
	cv::ocl::dilate(omatCornerHarris_, omatDialted, cv::Mat());

	cv::ocl::oclMat omatLocalMax;
	cv::ocl::compare(omatCornerHarris_, omatDialted, omatLocalMax, cv::CMP_EQ);


	//thresholding the corner
	cv::ocl::oclMat omatCorner;
	cv::ocl::oclMat omatTh;
	double threshold = 0.1 * maxStrength;
	cv::ocl::threshold(omatCornerHarris_, omatTh, threshold, 255, cv::THRESH_BINARY);
	omatTh.convertTo(omatCorner, CV_8U);

	// non-maxima suppression
	cv::ocl::bitwise_and(omatCorner, omatLocalMax, omatCorner);

	//download result
	//omatCornerHarris_.download(matResult_); //WARNING : blocking call

	cv::Mat cornetMat;

	omatCorner.download(cornetMat); //WARNING : blocking call
	

	
	std::vector<cv::Point> points;
	for( int y = 0; y < cornetMat.rows; y++ ) {
		const uchar* rowPtr = cornetMat.ptr<uchar>(y);
		for( int x = 0; x < cornetMat.cols; x++ ) {
 
			// if it is a feature point
			if (rowPtr[x]) {
 
				points.push_back(cv::Point(x,y));
			}
		} 
	}

	matResult_ = input;

	std::vector<cv::Point>::const_iterator it= points.begin();
	// for all corners
	while (it!=points.end()) {
 
		// draw a circle at each corner location
		cv::circle(matResult_,*it,3, cv::Scalar(255, 255, 255), 2);
		++it;
	}


	
	return 0;
}
