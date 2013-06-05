#ifndef EDGEL_HELPER_H
#define EDGEL_HELPER_H

#include <opencv\cv.h>
#include <iostream>

using namespace std;
using namespace cv;

#define INRANGE(val, low, high) ((val) >= (low) && (val) < (high))

Mat resizeToN(Mat& src, int N = 200)
{
	Mat ret(src);
	double longer = (src.rows > src.cols) ? src.rows : src.cols;
	double shorter = (src.rows > src.cols) ? src.cols : src.rows;

	if(longer <= N)
		ret = src;
	else
	{
		double multiplier = N;
		multiplier /= longer;
		
		int ret_rows = (src.rows > src.cols) ? longer * multiplier : shorter * multiplier;
		int ret_cols = (src.rows > src.cols) ? shorter * multiplier : longer * multiplier;
		resize(ret, ret, Size(ret_cols, ret_rows));
	}

	cout << "	resize from (" << src.rows << ", " << src.cols << ") to (" << ret.rows << ", " << ret.cols << ")" << endl;
	return ret;
}

unsigned int quantifiedAngle(double val)
{
	if(INRANGE(val, 0.0, 45.0))
		return 0;
	else if(INRANGE(val, 45.0, 90.0))
		return 1;
	else if(INRANGE(val, 90.0, 135.0))
		return 2;
	else if(INRANGE(val, 135.0, 180.0))
		return 3;
	else if(INRANGE(val, 180.0, 225.0))
		return 4;
	else if(INRANGE(val, 225.0, 270.0))
		return 5;
	else if(INRANGE(val, 270.0, 315.0))
		return 6;
	else if(INRANGE(val, 315.0, 360.0))
		return 7;
	else
	{
		cout << "invalid value " << val << "in function quantifiedAngle().";
		assert(false);
	}
}


Mat calculateOrientations(Mat& gradientX, Mat& gradientY)
{
    // Create container element
    Mat orientation = Mat(gradientX.rows, gradientX.cols, CV_32F);

    // Calculate orientations of gradients --> in degrees
    // Loop over all matrix values and calculate the accompagnied orientation
    for(int i = 0; i < gradientX.rows; i++)
	{
        for(int j = 0; j < gradientX.cols; j++)
		{
            // Retrieve a single value
            float valueX = gradientX.at<float>(i,j);
            float valueY = gradientY.at<float>(i,j);
            // Calculate the corresponding single direction, done by applying the arctangens function
            float result = fastAtan2(valueX,valueY);
            // Store in orientation matrix element
            orientation.at<float>(i,j) = result;
        }
    }

    return orientation;
}


#endif