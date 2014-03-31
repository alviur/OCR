#ifndef ANNTRAIN_H
#define ANNTRAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <qdebug.h>
#include <opencv2/opencv.hpp>
#include </home/lex/OpenCV-2.4.2/modules/nonfree/include/opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>



class AnnTrain
{
public:
    AnnTrain();
    ~AnnTrain();

    CvANN_MLP ann;//perceptron multicapa
    void train(cv::Mat trainData,cv::Mat classes,int nlayers,int numClasses);//entrena la red
    int evalNet(cv::Mat in, int numClasses);//evalua una entrada en la red neuronal


};

#endif // ANNTRAIN_H
