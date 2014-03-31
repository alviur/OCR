#include "smatch.h"


Smatch::Smatch()
{
}


Smatch::~Smatch()
{
}




/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla el match template de la Mat y retorna código de error.

***************************************************************************************************/

 int Smatch::MatchT(const cv::Mat &Mat,const cv::Mat &muestra, cv::Mat &resultado)
{

    if(!Mat.data) //comprueba si la imagen se cargo correctamente
           return 0;

    if((Mat.cols <  muestra.cols) || (Mat.rows  <  muestra.rows) ) //comprueba si la muestra es mas pequeña
           return 0;



    cv::Mat resultado2((Mat.cols) - (muestra.cols) + 1, (Mat.rows) - (muestra.rows) + 1,CV_32F,cv::Scalar(0));//crea una imagen de dimensiones predefinidas
    matchTemplate(Mat, muestra, resultado2,CV_TM_CCOEFF_NORMED);//se calcula el Match template
    resultado=resultado2.clone();
    return 1;



}



/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla el match con histograma de la Mat y retorna código de error.

***************************************************************************************************/


int Smatch::HistMatch(const cv::Mat &Mat, const cv::Mat &muestra, cv::Mat &resultado)
{



    //declaro arreglos necesarios
    int histsize[1];//numero de contenedores
    float hranges[2];//valores maximo y minimo de pixeles
    const float* ranges[1];
    int channels[1];//solo para 1 canal

    //inicializo
    histsize[0]=256;
    hranges[0]=0.0;
    hranges[1]=256.0;
    ranges[0]=hranges;
    channels[0]=0;

    cv::MatND hist;//contenedor de vects


     cv::calcHist(&muestra,//imagen
                 1,//solo una imagen
                channels, //canal utilizado
                cv::Mat(), //sin mascara
                hist, //donde sera almacenado
                1,
                histsize,
                ranges//rango de valores
                );


     cv::calcBackProject(&Mat, 1, channels,hist, resultado, ranges,255.0);

   return 1;

}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Halla el match con histograma de la Mat y retorna código de error.

***************************************************************************************************/



int Smatch::MatchSh(vector<vector<cv::Point> >  contours, vector<vector<cv::Point> >  contourMuestra, float &resul)
{
     resul= cv::matchShapes(contours,contourMuestra,CV_CONTOURS_MATCH_I1,0);
     return 1;

}


