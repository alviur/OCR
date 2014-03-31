
#define HOG_H
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include </home/lex/OpenCV-2.4.2/modules/nonfree/include/opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace cv;
using namespace std;

class Hog
{
public:
    Hog();
    ~Hog();


    HOGDescriptor H_featHog;
    vector<float> descriptorsValues;
    vector<Point> locations;


    vector<float> getHOG(cv::Mat& img,cv::Size winSize,cv::Size blockStride);


};
