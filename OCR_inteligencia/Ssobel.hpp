#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#include<iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
using namespace cv;
class Ssobel
{
    
    
public:
    
    int getVerticalC(cv::Mat src, int threshold);
    int getHorizontalC(cv::Mat src, int threshold);
    int I_ncambiosY;
    int I_ncambiosX;
    int I_ncontX;
    int I_ncontY;
    std::vector<std::vector<cv::Point> >I_ctnNumcontours;
    

};
