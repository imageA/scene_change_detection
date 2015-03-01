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
	//this->omatHist_ = cv::ocl::oclMat(1, 256, CV_8UC1);
	cv::ocl::oclMat omatGray( mat.rows, mat.cols, CV_8UC1 );
	
	cv::ocl::cvtColor( omatSrc_, omatGray, CV_BGR2GRAY );
	if(1){
		cv::Mat mat(omatGray.rows, omatGray.cols, omatGray.type());
		omatGray.download(mat);
		//cv::imshow("", mat);
		//cv::waitKey(0);
	}


	cv::ocl::calcHist(omatGray, omatHist_);


	cv::Mat matResult(omatHist_.rows, omatHist_.cols, omatHist_.type());
	omatHist_.download(matResult);

	for(int i=0; i < matResult.cols; i++){
		try{
			uchar value = matResult.at<uchar>(0, i);
			std::cout << i << " : " << value << std::endl;
		}
		catch(...){
			
		}
	}


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
