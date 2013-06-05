#ifndef EDGEL_DIC_H
#define EDGEL_DIC_H

#include <map>
#include <string>
#include "edgel.h"

void createEdgelDic(std::vector<char*>& const ctr_names, std::map<int, Content_Vec>& edgel_dic, std::vector<int>& edgel_counter);
void createEdgelDic(std::vector<char*>& const ctr_names, std::map<int, Content_Vec>& edgel_dic, std::vector<int>& edgel_counter, std::vector<cv::Mat>& ctr_base);
void createEdgelDic(std::vector<std::string>& const ctr_names, std::map<int, Content_Vec>& edgel_dic, std::vector<int>& edgel_counter, std::vector<cv::Mat>& ctr_base);

void cvtToOrntImg(cv::Mat& rawImg);
void analyzeEdgelDic(std::map<int, Content_Vec>& const edgel_dic, bool const flag = false);
void computeDocScore(cv::Mat skch, std::map<int, Content_Vec>& const edgel_dic, std::vector<double>& score);
void makeEdgelDicFile(std::map<int, Content_Vec>& edgel_dic);

#endif

