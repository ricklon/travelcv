#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/nonfree/features2d.hpp"


namespace cv
{
    using std::vector;
}

const float kRescaleFactor = 0.35;

int main( int argc, char** argv )
{
	Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if(img1.empty() || img2.empty())
	{
		printf("Can't read one of the images\n");
		return -1;
	}

	// detecting keypoints
	SurfFeatureDetector detector(400);
	Svector<KeyPoint> keypoints1, keypoints2;
	Sdetector.detect(img1, keypoints1);
	Sdetector.detect(img2, keypoints2);

	// computing descriptors
	SSurfDescriptorExtractor extractor;
	SMat descriptors1, descriptors2;
	Sextractor.compute(img1, keypoints1, descriptors1);
	Sextractor.compute(img2, keypoints2, descriptors2);

	// matching descriptors
	SBruteForceMatcher<L2<float> > matcher;
	Svector<DMatch> matches;
	Smatcher.match(descriptors1, descriptors2, matches);

	// drawing the results
	SnamedWindow("matches", 1);
	SMat img_matches;
	SdrawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
	Simshow("matches", img_matches);
	SwaitKey(0);
}
