#ifndef __SCENE_CHANGE_DETECTOR_H
#define __SCENE_CHANGE_DETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <string>

class SceneChangeDetector{
private:
	cv::ocl::oclMat omatInput_;
	cv::ocl::oclMat omatInputGray_;

	cv::Mat matResult_;
public:
	SceneChangeDetector();
	
	int doWork(cv::Mat input);

	cv::Mat& resultMat() { return matResult_; }

};



#endif