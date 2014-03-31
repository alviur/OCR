#ifndef INTEGRALPROY_H
#define INTEGRALPROY_H
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class IntegralProy
{
public:
    IntegralProy();
    ~IntegralProy();



    //Metodos
    vector<double> integralX(cv::Mat M_imgSource);
    vector<double> integralY(cv::Mat M_imgSource);
    vector<double> integralYline(cv::Mat M_imgSource);
};

#endif // INTEGRALPROY_H
