#include "integralproy.h"

IntegralProy::IntegralProy()
{
}


IntegralProy::~IntegralProy()
{
}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla la integral de proyeccion en direccion X.

***************************************************************************************************/


vector<double> IntegralProy::integralX(cv::Mat M_imgSource)
{
    int value=0;
    vector<double> V_vectIntegral(M_imgSource.size().width);


     for(int i=0;i< M_imgSource.size().width;i++){//hasta el ancho de la imagen
         for(int j=0;j< M_imgSource.size().height;j++){//hasta el alto de la imagen


                value+=M_imgSource.at<uchar>(j,i);

           }

        V_vectIntegral[i]=value;
        value=0;
       }


     return V_vectIntegral;


}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla la integral de proyeccion en direccion Y.

***************************************************************************************************/

vector<double> IntegralProy::integralY(cv::Mat M_imgSource)
{

    int value=0;
    vector<double> V_vectIntegral(M_imgSource.size().height);

    //conversion imagen flotante a entera
    double minVal, maxVal;
    minMaxLoc(M_imgSource, &minVal, &maxVal); //find minimum and maximum intensities
    Mat draw;
    M_imgSource.convertTo(M_imgSource, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));


    for(int j=0;j< M_imgSource.size().height;j++){//hasta el alto de la imagen
     for(int i=0;i< M_imgSource.size().width;i++){//hasta el ancho de la imagen



                value=value +  M_imgSource.at<uchar>(j,i);

           }

        V_vectIntegral[j]=value;

        value=0;
       }


     return V_vectIntegral;
}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla la integral de proyeccion en direccion Y de cada fila

***************************************************************************************************/

vector<double> IntegralProy::integralYline(cv::Mat M_imgSource)
{

    int valueant=0;
      int value=0;
    vector<double> V_vectCambios(M_imgSource.size().height);


    for(int j=0;j< M_imgSource.size().height;j++){//hasta el alto de la imagen

        V_vectCambios[j]=0;//inicializaicio fila
     for(int i=0;i< M_imgSource.size().width;i++){//hasta el ancho de la imagen



                value=M_imgSource.at<uchar>(j,i);//asigna valor actual
                if(value!=valueant)V_vectCambios[j]++;
                valueant=value;

           }



       }


     return V_vectCambios;
}
