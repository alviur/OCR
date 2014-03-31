#include "anntrain.h"

AnnTrain::AnnTrain()
{
}

AnnTrain::~AnnTrain()
{
}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Entrena una red neuronal, el parametro classes deberan ser vectores fila en binario

***************************************************************************************************/

void AnnTrain::train(cv::Mat trainData, cv::Mat classes, int nlayers,int numClasses)
{
    cv::Mat layerSizes(1,3,CV_32SC1);//alojara los datos
    layerSizes.at<int>(0)=trainData.cols;//cantidad de caracteristicas
    layerSizes.at<int>(1)=nlayers;//numero de capas ocultas
    layerSizes.at<int>(2)=numClasses;//numero de clases

   ann.create(layerSizes,CvANN_MLP::SIGMOID_SYM,1,1);//inicializa la red

//   cv::Mat trainClasses;//matriz que contendra n(cantidad de muestras) por m clases

//   trainClasses.create(trainData.rows,numClasses,CV_32FC1);//crea la matriz con las caracteristicas deseadas


   cv::Mat weights(1,trainData.rows,CV_32FC1,cv::Scalar::all(1));//crea e inicializa todos los pesos en 1

   //Entrenamiento

   ann.train(trainData,classes,weights);//entrena la red

   //////////////////////////// inicio guardar red  ////////////////////////////////
   cv::FileStorage fs("/home/lex/Cv/mlp.xml", cv::FileStorage::WRITE); // or xml
   ann.write(*fs, "Net1"); // don't think too much about the deref, it casts to a FileNode
   //////////////////////////// fin guardar red  ////////////////////////////////


}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: evalua la red neuronal

***************************************************************************************************/
int AnnTrain::evalNet(cv::Mat in,int numClasses)
{

    cv::Mat output(1,numClasses,CV_32FC1);
    ann.predict(in,output);//calcula la salida de la red
    cv::Point maxLoc;//ubicacion del valor maximo
    double maxVal;//valor maximo de la salida
    minMaxLoc(output,0,&maxVal,0,&maxLoc);//halla el maximo
    return maxLoc.x;//retorna la posicion del maximo

}
