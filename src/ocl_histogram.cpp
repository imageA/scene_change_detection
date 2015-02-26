#include "ocl_histogram.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>


OclHist::OclHist(std::string filename){
	IplImage *img = cvLoadImage(filename.c_str());
	cv::Mat mat(img);

	cv::imshow("", mat);
	cv::waitKey(0);

	this->omatSrc_ = cv::ocl::oclMat(mat);
	this->omatSrc_ = cv::ocl::oclMat(mat.rows, mat.cols, CV_8UC1);
	cv::ocl::calcHist(omatSrc_, omatHist_);


}

void OclHist::printf(){
	cv::Mat mat(omatHist_.rows, omatHist_.cols, omatHist_.type());
	omatHist_.download(mat);

	for(int i=0; i < mat.cols; i++){
		try{
			uchar value = mat.at<uchar>(0, i);
			std::cout << i << " : " << value << std::endl;
		}
		catch(...){
			
		}
		
	}


}