#include <map>
#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <fstream>
#include "edgel.h"
#include "edgel_dictionary.h"
#include "edgel_helper_funcitons.h"

using namespace std;
using namespace cv;

#define TOLE_RADIUS 2

void createEdgelDic(vector<char*>& const ctr_names, map<int, Content_Vec>& edgel_dic, vector<int>& edgel_counter)
{
	//read in all contours into contour base, ctr_base.
	vector<Mat> ctr_base(ctr_names.size());
	for(int docID = 0; docID < ctr_names.size(); docID++)
	{
		Mat tmp = imread(ctr_names[docID], 0);//resizeToN(imread(ctr_names[docID], 0), 200);
		threshold(tmp, ctr_base[docID], 230, 255, THRESH_BINARY_INV);
		//namedWindow("threshold", CV_WINDOW_NORMAL);
		//imshow("threshold", ctr_base[docID]);
		//waitKey();
		//imshow("ctr_base" ,ctr_base[docID]);
	}

	//cout << endl << "	Start inserting edgel dicitonary entries..." << endl;

	//for every contour image
	for(int docID = 0; docID < ctr_base.size(); docID++)
	{
		//cout << "	Processing edgel entries of contour image (docID = " << docID << ").." << endl;

		//convert this contour image to orientation image
		cvtToOrntImg(ctr_base[docID]);

		//initialize counter
		edgel_counter[docID] = 0;

		//for every edgel in the ornt img
		for(int x = 0; x < ctr_base[docID].rows; x++)
		{
			for(int y = 0; y < ctr_base[docID].cols; y++)
			{
				//val is the value of orientation at (x, y)
				double val = ctr_base[docID].at<float>(x, y);
				if (val != 0.0)
				{
					Edgel egl(x, y, quantifiedAngle(val));
					edgel_dic[egl.idx()].push_back(docID);
					edgel_counter[docID]++;
				}
			}
		}
	}

}


//output ctr_base to check the contour when retrieval
void createEdgelDic(vector<char*>& const ctr_names, map<int, Content_Vec>& edgel_dic, vector<int>& edgel_counter, vector<Mat> & ctr_base)
{
	//read in all contours into contour base, ctr_base.
	//vector<Mat> ctr_base(ctr_names.size());
	for(int docID = 0; docID < ctr_names.size(); docID++)
	{
		Mat tmp = imread(ctr_names[docID], 0);//resizeToN(imread(ctr_names[docID], 0), 200);
		threshold(tmp, ctr_base[docID], 220, 255, THRESH_BINARY_INV);
		
		namedWindow("threshold", CV_WINDOW_NORMAL);
		imshow("threshold", ctr_base[docID]);
		waitKey();
		imshow("ctr_base" ,ctr_base[docID]);
	}

	//cout << endl << "	Start inserting edgel dicitonary entries..." << endl;

	//for every contour image
	for(int docID = 0; docID < ctr_base.size(); docID++)
	{
		//cout << "	Processing edgel entries of contour image (docID = " << docID << ").." << endl;

		//convert this contour image to orientation image
		cvtToOrntImg(ctr_base[docID]);

		//initialize counter
		edgel_counter[docID] = 0;

		//for every edgel in the ornt img
		for(int x = 0; x < ctr_base[docID].rows; x++)
		{
			for(int y = 0; y < ctr_base[docID].cols; y++)
			{
				//val is the value of orientation at (x, y)
				double val = ctr_base[docID].at<float>(x, y);
				if (val != 0.0)
				{
					Edgel egl(x, y, quantifiedAngle(val));
					edgel_dic[egl.idx()].push_back(docID);
					edgel_counter[docID]++;
				}
			}
		}
	}

}


//output ctr_base to check the contour when retrieval
//string filename version
void createEdgelDic(vector<string>& const ctr_names, map<int, Content_Vec>& edgel_dic, vector<int>& edgel_counter, vector<Mat> & ctr_base)
{
	//read in all contours into contour base, ctr_base.
	//vector<Mat> ctr_base(ctr_names.size());
	for(int docID = 0; docID < ctr_names.size(); docID++)
	{
		Mat tmp = imread(ctr_names[docID], 0);//resizeToN(imread(ctr_names[docID], 0), 200);
		//imshow("ctr_base" ,tmp);
		threshold(tmp, ctr_base[docID], 220, 255, THRESH_BINARY_INV);
		
		//namedWindow("threshold", CV_WINDOW_NORMAL);
		//imshow("threshold", ctr_base[docID]);
		//waitKey();
	}

	//cout << endl << "	Start inserting edgel dicitonary entries..." << endl;

	//for every contour image
	for(int docID = 0; docID < ctr_base.size(); docID++)
	{
		//cout << "	Processing edgel entries of contour image (docID = " << docID << ").." << endl;

		//convert this contour image to orientation image
		cvtToOrntImg(ctr_base[docID]);

		//initialize counter
		edgel_counter[docID] = 0;

		//for every edgel in the ornt img
		for(int x = 0; x < ctr_base[docID].rows; x++)
		{
			for(int y = 0; y < ctr_base[docID].cols; y++)
			{
				//val is the value of orientation at (x, y)
				double val = ctr_base[docID].at<float>(x, y);
				if (val != 0.0)
				{
					Edgel egl(x, y, quantifiedAngle(val));
					edgel_dic[egl.idx()].push_back(docID);
					edgel_counter[docID]++;
				}
			}
		}
	}

}


void cvtToOrntImg(Mat& src)
{
	Mat dx, dy;
	Sobel(src, dx, CV_32F, 1, 0, 3);
	Sobel(src, dy, CV_32F, 0, 1, 3);
	//imshow("dx", dx);
	//imshow("dy", dy);
	//waitKey();
	src = calculateOrientations(dx, dy);
}



void analyzeEdgelDic(map<int, Content_Vec>& const edgel_dic, bool const flag)
{
	cout << "	Number of edgel entries : " << edgel_dic.size() << endl;
	if(!flag)
		return;
	else
	{
		cout << endl << "	Exhaustive checking the number of docs for each edgel entry" << endl;
		for(map<int, Content_Vec>::iterator iter = edgel_dic.begin();
			iter != edgel_dic.end(); iter++)
		{
			cout << "	edgel_dic[" << iter->first << "].size() = " << iter->second.size() << endl;
		}
	}
}


void computeDocScore(Mat skch, map<int, Content_Vec>& const edgel_dic, vector<double>& score)
{
	
	cvtToOrntImg(skch);

	cout << skch;
	imshow("ornt_skch", skch);
	waitKey();

	for(int x = 0; x < skch.rows; x++)
	{
		for(int y = 0; y < skch.cols; y++)
		{
			double val = skch.at<float>(x, y);
			if (val != 0.0)
			{
				//for all edgel entries within the tolerance radius
				for(int rx = max(0, x - TOLE_RADIUS); rx < min(skch.rows, x + TOLE_RADIUS + 1); rx++)
				{
					for(int ry = max(0, y - TOLE_RADIUS); ry < min(skch.cols, y + TOLE_RADIUS + 1); ry++)
					{
						Edgel egl(rx, ry, quantifiedAngle(val));
						if(edgel_dic.find(egl.idx()) != edgel_dic.end())
						{
							for(Content_Vec::iterator iter = edgel_dic[egl.idx()].begin();
								iter != edgel_dic[egl.idx()].end(); iter++)
							score[*iter]++;
						}
					}
				}
			}
		}
	}
}



void makeEdgelDicFile(map<int, Content_Vec>& edgel_dic)
{
	ofstream myfile;
	myfile.open("edgel_dic.txt");
	
	for(map<int, Content_Vec>::iterator map_iter = edgel_dic.begin(); map_iter != edgel_dic.end(); map_iter++)
	{
		myfile << map_iter->first << " ";
		
		for(Content_Vec::iterator vec_iter = map_iter->second.begin(); vec_iter != map_iter->second.end(); vec_iter++)
			myfile << *vec_iter << " ";
		
		myfile << endl;

	}
}