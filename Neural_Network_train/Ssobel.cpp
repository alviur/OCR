#include"Ssobel.hpp"

int Ssobel::getVerticalC(cv::Mat src, int threshold=190)
{
    cv::imshow("placa",src);
    cv::Mat I_contYComp;
    cv::Mat I_ctnContYComp;

    cv::Sobel(src,I_contYComp,CV_8U,1,0);
    cv::threshold(I_contYComp,I_contYComp,threshold,255,0);
    cv::imshow("placa derivada vertical",I_contYComp);
    //Simage::Pixval(&I_contYComp, 200 ,  &I_ncambiosY);

    int value=0;
    int ncambios=0;
    for(int i=0;i< I_contYComp.size().width;i++)
    {//hasta el ancho de la imagen
            for(int j=0;j< I_contYComp.size().height;j++)
            {//hasta el alto de la imagen
                 value=I_contYComp.at<uchar>(j,i);
                 if(value > 200)ncambios++;

            }
     }

    cv::Canny(I_contYComp,I_ctnContYComp,100,255);
    cv::imshow("contorno Y",I_ctnContYComp);
    cv::findContours(I_ctnContYComp,I_ctnNumcontours,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    I_ncontY=I_ctnNumcontours.size();

    return I_ncontY;
}

int Ssobel::getHorizontalC(cv::Mat src, int threshold=190)
{
    cv::imshow("placa",src);
    cv::Mat I_contXComp;
    cv::Mat I_ctnContXComp;

    cv::Sobel(src,I_contXComp,CV_8U,0,1);
    cv::threshold(I_contXComp,I_contXComp,threshold,255,0);
    cv::imshow("placa derivada horizontal",I_contXComp);
    //Simage::Pixval(&I_contXComp, 200 ,  &I_ncambiosX);

    int value=0;
    int ncambios=0;
    for(int i=0;i< I_contXComp.size().width;i++)
    {//hasta el ancho de la imagen
            for(int j=0;j< I_contXComp.size().height;j++)
            {//hasta el alto de la imagen
                 value=I_contXComp.at<uchar>(j,i);
                 if(value > 200)ncambios++;

            }
     }

    cv::Canny(I_contXComp,I_ctnContXComp,100,255);
    cv::imshow("contorno X",I_ctnContXComp);
    cv::findContours(I_ctnContXComp,I_ctnNumcontours,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    I_ncontX=I_ctnNumcontours.size();

    return I_ncontX;
    
}
