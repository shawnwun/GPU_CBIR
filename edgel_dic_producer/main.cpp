#include <opencv\cv.h>                 
#include <opencv\highgui.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "arg_producer.h"
#include "edgel_dictionary.h"
#include "edgel.h"

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
	
	cout << "Phase : Processing cmd arguments" << endl;
	
	vector<string> ucm_files;
	vector<string> img_files;
	char sdir[256], filter[256];
	strcpy(sdir, "D:\\Visual Studio Projects\\edgel_dic_producer\\Release\\rename");
	strcpy(filter, "*.ucm.jpg");
	fileInFolder(sdir, filter, ucm_files);
	strcpy(filter, "*.img.jpg");
	fileInFolder(sdir, filter, img_files);
	cout << endl;


	cout << "Phase : creatEdgelDic()" << endl;

	clock_t clk_beg = clock();
	
	map<int, Content_Vec> edgel_dic;
	vector<int> edgel_counter(ucm_files.size());
	vector<Mat> ctr_base(ucm_files.size());
	createEdgelDic(ucm_files, edgel_dic, edgel_counter, ctr_base); 
	
	clock_t clk_end = clock();
	
	cout << "Elapsed Time: " << double(clk_end - clk_beg) / CLOCKS_PER_SEC << " s."<< endl;
    
	cout << "Phase : analyzeEdgelDic()" << endl;
	analyzeEdgelDic(edgel_dic);

	cout << "Edgel dictionary based on " << ucm_files.size() << " contour images has been successfully built!" << endl;
	
	cout << "Writing edgel_dic into file" << endl;
	makeEdgelDicFile(edgel_dic);
	makeEdgelCtrFile(edgel_counter);


	return 0;
}