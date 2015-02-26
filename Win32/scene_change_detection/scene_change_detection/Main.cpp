#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include "..\\..\\..\\src\ocl_histogram.hpp"

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

    cvDestroyWindow("result");

    return ;
}


#define SAMPLE_IMG "lena.jpg"


int main( int argc, const char** argv )
{
	OclHist oclHist(SAMPLE_IMG);
	oclHist.printf();

	return 0;
}