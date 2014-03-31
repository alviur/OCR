#ifndef SMATCH_H
#define SMATCH_H

#include "Smatch_global.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

using namespace std;


class SMATCHSHARED_EXPORT Smatch
{
public:
    Smatch();
    ~Smatch();

 static  int MatchT(const cv::Mat &Mat,const cv::Mat &muestra, cv::Mat &resultado);
 static  int HistMatch(const cv::Mat &Mat,const cv::Mat & muestra, cv::Mat &resultado);
 static  int MatchSh(vector<vector<cv::Point> > contours, vector<vector<cv::Point> > contourMuestra,float &resul);
};

#endif // SMATCH_H
