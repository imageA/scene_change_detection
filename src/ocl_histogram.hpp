#ifndef __OCL_HISTOGRAM_H
#define __OCL_HISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <string>

class OclHist{
private:
	cv::ocl::oclMat omatSrc_;
	cv::ocl::oclMat omatHist_;

public:
	OclHist(std::string filename);	
	
	void printf();
	
};



#endif