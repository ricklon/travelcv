#include <stdio.h>
#include <iostream>
#include <cv.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace cv;

void readme();
Mat hsv_img1, hsv_img2, mask_img1, mask_img2;

/** @function main */
int main( int argc, char** argv )
{
  if( argc != 3 )
  { readme(); return -1; }

  Mat img_1 = imread( argv[1]);//, CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_2 = imread( argv[2]);//, CV_LOAD_IMAGE_GRAYSCALE );

	  cvtColor(img_1, hsv_img1, COLOR_BGR2HSV);
		cvtColor(img_2, hsv_img2, COLOR_BGR2HSV);
    inRange(hsv_img1, Scalar(0, 120, 120), Scalar(30, 255, 255), mask_img1);
		inRange(hsv_img1, Scalar(0, 120, 120), Scalar(30, 255, 255), mask_img2);

    //11     lower_green = np.array([0, 0, 0])
    ///12     upper_green = np.array([60, 255, 255])
    //13     mask = cv2.inRange(hsv, lower_green, upper_green)
    //14     res = cv2.bitwise_and(img, img, mask=mask)
    //15     scale_width, scale_height = scale(img)


  if( !img_1.data || !img_2.data )
  { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

  //-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 400;

  SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints_1, keypoints_2;

  detector.detect( mask_img1, keypoints_1 );
  detector.detect( mask_img2, keypoints_2 );

  //-- Draw keypoints
  Mat img_keypoints_1; Mat img_keypoints_2;

  drawKeypoints( img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  drawKeypoints( img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  resize(img_keypoints_1, img_keypoints_1, Size(0, 0), 0.35, 0.35, INTER_CUBIC);
  resize(img_keypoints_2, img_keypoints_2, Size(0, 0), 0.35, 0.35);
  //-- Show detected (drawn) keypoints
  imshow("Keypoints 1", img_keypoints_1 );
  imshow("Keypoints 2", img_keypoints_2 );

  waitKey(0);

  return 0;
  }

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl; }
