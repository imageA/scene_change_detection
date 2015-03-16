#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ocl/ocl.hpp>


#include <iostream>
#include <stdio.h>

#include "..\\..\\..\\src\\ocl_histogram.hpp"
#include "..\\..\\..\\src\\SceneChangeDetector.hpp"

using namespace std;
using namespace cv;

using namespace cv::ocl;

void camera_test(){

    int id = -1;
	for(int i=0; i<15; i++){
		VideoCapture cap(i);
		if(cap.isOpened()){
			id = i; break;
		}
	}
	CvCapture* capture = 0;
    Mat frame;

    capture = cvCaptureFromCAM( id ); //0=default, -1=any camera, 1..99=your camera
    if(!capture) cout << "No camera detected" << endl;
	

    cvNamedWindow( "result", 1 );

    if( capture )
    {
        cout << "In capture ..." << endl;
        for(;;)
        {
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;

			cv::imshow("result", frame);
            if( waitKey( 10 ) >= 0) {
                cvReleaseCapture( &capture );
				break;
			}
        }
	}
    waitKey(0);

}


void camera_work(){
	
	SceneChangeDetector scDetector;


    int id = -1;
	for(int i=0; i<15; i++){
		VideoCapture cap(i);
		if(cap.isOpened()){
			id = i; break;
		}
	}
	CvCapture* capture = 0;
    Mat frame;

    capture = cvCaptureFromCAM( id ); //0=default, -1=any camera, 1..99=your camera
    if(!capture) cout << "No camera detected" << endl;
	

    cvNamedWindow( "result", 1 );

    if( capture )
    {
        cout << "In capture ..." << endl;
        for(;;)
        {
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
            
			scDetector.doWork(frame);

			cv::imshow("result", scDetector.resultMat());
			if( waitKey( 10 ) >= 0 ){
                cvReleaseCapture( &capture );
				break;
			}
        }
	}
    waitKey(0);

    cvDestroyWindow("result");

    return ;
}


#define SAMPLE_IMG "lena.jpg"

void image_work(){
	
	SceneChangeDetector scDetector;

	IplImage *img = cvLoadImage(SAMPLE_IMG);
	cv::Mat frame(img);
	
	cv::imshow("", frame);
	cv::waitKey(0);

	scDetector.doWork(frame);
	
	cv::Mat &result = scDetector.resultMat();
	
	cv::imshow("result", result);
	cv::waitKey(0);

}


int main( int argc, const char** argv )
{
	
	//image_work();
	camera_work();
	//camera_test();
	
	//cv::ocl::BackgroundSubtractor a;
	
	//OclHist oclHist(SAMPLE_IMG);
	//oclHist.printf();

	

	return 0;
}
