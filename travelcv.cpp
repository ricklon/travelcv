#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

using namespace cv;

const float kRescaleFactor = 0.35;


/** @function main */
int main( int argc, char** argv )
{
    Mat src = imread( argv[1], 1 );
    Mat dst;
    Mat img_object = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    Mat work_object;

    cv::Canny(src, dst, 100, 100, 3);

    resize(dst, dst, cvSize(0, 0), kRescaleFactor, kRescaleFactor);

    namedWindow( "Source Window", CV_WINDOW_NORMAL );
    imshow("Source Window",dst);

    cv::threshold(img_object, work_object, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
    // find contours (if always so easy to segment as your image, you could just add the black/rect pixels to a vector)
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(work_object,work_object, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    resize(img_object, work_object, cvSize(0, 0), kRescaleFactor, kRescaleFactor);
  //  cv::Canny(work_object, work_object, 100, 100, 3);
    namedWindow( "Work Window", CV_WINDOW_NORMAL );
    imshow("Work Window",work_object);

    waitKey(0);
    return 0;
}

/** @function readme */
void readme()
{ std::cout << " Usage: ./travelcv <img1>" << std::endl; }
