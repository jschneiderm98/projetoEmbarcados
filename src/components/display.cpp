#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#define thresh 100
using namespace cv;
using namespace std;
Mat src_gray;
RNG rng(12345);

bool compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {
    double i = fabs( contourArea(cv::Mat(contour1)) );
    double j = fabs( contourArea(cv::Mat(contour2)) );
    return ( i < j );
}

float imageProcess(char* image)
{
    
    Mat src = imread( samples::findFile( image ) );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    adaptiveThreshold(src_gray, src_gray, 80, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY, 51, 12);
    GaussianBlur(src_gray, src_gray,Size(7, 7), 0);
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, 2*thresh);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    std::sort(contours.begin(), contours.end(), compareContourAreas);
    vector<Moments> mu(contours.size() );
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
    drawContours( drawing, contours, contours.size()-1, color, 2, LINE_8, hierarchy, 0 );
    //imshow( "Contours", drawing );
    //cout << "Bread Area: " << contourArea(contours[contours.size()-1]) << endl;
    return contourArea(contours[contours.size()-1]);
    waitKey();
}

float webcamShot(){
  float size;
  system("fswebcam /tmp/dough.jpg");
  size = imageProcess("/tmp/dough.jpg");
  return size;
}
