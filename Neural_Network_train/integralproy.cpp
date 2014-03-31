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


                value=value +  M_imgSource.at<uchar>(j,i);

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


    for(int j=0;j< M_imgSource.size().height;j++){//hasta el alto de la imagen
     for(int i=0;i< M_imgSource.size().width;i++){//hasta el ancho de la imagen



                value=value +  M_imgSource.at<uchar>(j,i);

           }

        V_vectIntegral[j]=value;

        value=0;
       }


     return V_vectIntegral;
}
