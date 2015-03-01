#include "SceneChangeDetector.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

SceneChangeDetector::SceneChangeDetector(){
	
}

int SceneChangeDetector::doWork(cv::Mat input){

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
	
	//upload input frame
	omatInput_.upload(input);

	//process
	cv::ocl::cvtColor(omatInput_, omatInputGray_, CV_BGR2GRAY);
	
	//download result
	omatInputGray_.download(matResult_);

	
	return 0;
}
