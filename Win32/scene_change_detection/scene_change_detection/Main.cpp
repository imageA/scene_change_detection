#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include "..\\..\\..\\src\\ocl_histogram.hpp"
#include "..\\..\\..\\src\\SceneChangeDetector.hpp"

using namespace std;
using namespace cv;




void camera_test(){

    int id = -1;
	for(int i=0; i<15; i++){
		VideoCapture cap(i);
		if(cap.isOpened()){
			id = i; break;
		}
	}
	CvCapture* capture = 0;
    Mat frame, frameCopy, image;

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
            if( frame.empty() )
                break;
            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );


			cv::imshow("result", frameCopy);
            if( waitKey( 10 ) >= 0 )
                cvReleaseCapture( &capture );
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
    Mat frame, frameCopy, image;
	Mat resultFrame;

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
            if( frame.empty() )
                break;
            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );

			scDetector.doWork(frameCopy);
			resultFrame = scDetector.resultMat();			

			cv::imshow("result", resultFrame);
            if( waitKey( 10 ) >= 0 )
                cvReleaseCapture( &capture );
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

	//OclHist oclHist(SAMPLE_IMG);
	//oclHist.printf();

	

	return 0;
}