#include <stdio.h>
#include "cv.h"
#include "highgui.h"

void mouseHandler( int event, int x, int y, int flags, void *param );
CvCapture* g_capture = NULL;

int g_slider_position_h1 = 0;
int g_slider_position_s1 = 0;
int g_slider_position_v1 = 0;
int g_slider_position_a1 = 0;
int g_slider_position_h2 = 0;
int g_slider_position_s2 = 0;
int g_slider_position_v2 = 0;
int g_slider_position_a2 = 0;
int g_slider_position_sel = 0;




IplImage *src_image;
IplImage *hsv_image;

CvScalar  hsv_min = cvScalar(120, 120, 120, 120);
CvScalar  hsv_max = cvScalar(134, 134, 134, 134);


int main( int argc, char** argv )
{
	int key = 0;
	
	src_image = cvLoadImage( argv[1]);
	hsv_image = cvCreateImage( cvGetSize(src_image), IPL_DEPTH_8U , 3);
	cvCvtColor(src_image, hsv_image, CV_BGR2HSV);
	IplImage* hsv_filt  = cvCreateImage( cvGetSize(src_image), IPL_DEPTH_8U , 1);
	
	cvNamedWindow( "src",CV_WINDOW_NORMAL);
	cvNamedWindow( "filterd",CV_WINDOW_NORMAL);
	cvSetMouseCallback( "src", mouseHandler, NULL );
	
	
	while( key != 27)
	{
		cvCreateTrackbar("select","src",&g_slider_position_sel,1,NULL);
		
		cvCreateTrackbar("Hue 1","src",&g_slider_position_h1,255,NULL);
		cvCreateTrackbar("Sat 1","src",&g_slider_position_s1,255,NULL);
		cvCreateTrackbar("Val 1","src",&g_slider_position_v1,255,NULL);
		cvCreateTrackbar("alp 1","src",&g_slider_position_a1,255,NULL);
	
		cvCreateTrackbar("Hue 2","src",&g_slider_position_h2,255,NULL);
		cvCreateTrackbar("Sat 2","src",&g_slider_position_s2,255,NULL);
		cvCreateTrackbar("Val 2","src",&g_slider_position_v2,255,NULL);
		cvCreateTrackbar("alp 2","src",&g_slider_position_a2,255,NULL);
		
		hsv_min.val[0] = g_slider_position_h1;
  		hsv_min.val[1] = g_slider_position_s1;
  		hsv_min.val[2] = g_slider_position_v1;
  		hsv_min.val[3] = g_slider_position_a1;
  		
  		hsv_max.val[0] = g_slider_position_h2;
  		hsv_max.val[1] = g_slider_position_s2;
  		hsv_max.val[2] = g_slider_position_v2;
		hsv_min.val[3] = g_slider_position_a1;
		
		cvShowImage("src",src_image);
		cvCvtColor(src_image, hsv_image, CV_BGR2HSV);
		cvInRangeS (hsv_image, hsv_min, hsv_max, hsv_filt);
		cvShowImage("filterd",hsv_filt);
		key = cvWaitKey( 30 );
	}
	
	
	
	
return 1;
}


void mouseHandler( int event, int x, int y, int flags, void *param )
{  
	if( event == CV_EVENT_LBUTTONUP ) 
	{
        	CvScalar col = cvGetAt(hsv_image,x,y);
        	
        	if(g_slider_position_sel==0)
        	{
        		g_slider_position_h1 = col.val[0];
        		g_slider_position_s1 = col.val[1];
        		g_slider_position_v1 = col.val[2];
        		g_slider_position_a1 = col.val[3];
        	}
        	else if(g_slider_position_sel==1)
        	{
        		
        		g_slider_position_h2  = col.val[0];
        		g_slider_position_s2  = col.val[1];
        		g_slider_position_v2  = col.val[2];
	        	g_slider_position_a2  = col.val[3];
	        }
        }
}


