/***************************************************************************
* This file is part of GNoiseSuppression.
* Copyright (C) 2012 German Diez, Nicanor Garcia

* GNoiseSuppression is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* GNoiseSuppression is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with GNoiseSuppression.  If not, see <http://www.gnu.org/licenses/>.


****************************************************************************
* Authors: German Diez, Nicanor Garcia
* Contact:
* Date: 13/01/2013
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "option.h"
#include "QFileDialog"

#include<QMovie>
#include<QLabel>

//**********************************************************************************************************
/*
 * Constructor por defecto
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Inicializar la interfaz grafica
    type=4;
    cleanMod=5;
    thrMod=1;
    //process=new Procesamiento(); // Reservar memoria dinamica



    matrizReduccion.load("matrizReduccion.txt");//cargo matriz de reduccion de PCA

    playFlag=false;
    loadflag=false;
    processflag=false;


    /*connect(ui->cleanPlot,SIGNAL(play()),this,SLOT(play_clean_signal()));
    connect(ui->cleanPlot,SIGNAL(playsegment()),this,SLOT(play_clean_segment()));
    connect(ui->cleanPlot,SIGNAL(sstop()),this,SLOT(stopbutton()));


    connect(ui->signalPlot,SIGNAL(play()),this,SLOT(play_signal()));
    connect(ui->signalPlot,SIGNAL(playsegment()),this,SLOT(play_segment()));
    connect(ui->signalPlot,SIGNAL(sstop()),this,SLOT(stopbutton()));*/


}
//************************************************************************************************************
/*
 * Destructor
 */

MainWindow::~MainWindow()
{
    // Limpiar memoria dinamica
    delete process;
    delete ui;
}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Extrae firma de la imagen
***************************************************************************************************/

void get_firma_binary_changes(cv::Mat src, int num_lines, int *src_firma)
{
    num_lines=num_lines+1;// se le suma 1 para conciderar las lineas horizontales y verticales
    double divisiones= 3.14159265358979323846 /(num_lines*2);// para hallar la separacion en radianes entre lineas
    int y;// variable auxiliar usada para describir los rayos a partir de los cuales se analiza la imagen
    int y_;// variable auxiliar usada para describir los rayos a partir de los cuales se analiza la imagen
    int x;// variable auxiliar usada para describir los rayos a partir de los cuales se analiza la imagen
    int x_;// variable auxiliar usada para describir los rayos a partir de los cuales se analiza la imagen
    int pixel_ant;// variable auxiliar usada para analizar los cambios en el valor de los pixeles a lo largo de los radios
    int pixel_init;// variable auxiliar usada para analizar los cambios en el valor de los pixeles a lo largo de los radios
    int cont_cambios=0;// contador de cambios de valor en los pixeles a lo largo de los radios
    double m=0;//variable auxiliar que guarda la pendiente de cada radio
    int index=0;// contador auxiliar usado para archivar en src_firma los cambios en cada radio

    for(int i=0;i<=num_lines;i++)// ciclo principal donde se trazan los radios
    {
        m=(double)i*divisiones;// ajuste de la pendiente para cada iteracion

        if(m>3.14159265358979323846/2.1)// para evitar problemas con la discontinuidad de la tangente en pi/2
        {
            for(int y=0; y<src.rows/2-1 ;y++)// trazado del radio inferior vertical
            {
                if(y==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y+src.rows/2,src.cols/2);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y+src.rows/2,src.cols/2))
                    {
                        pixel_ant=src.at<uchar>(y+src.rows/2,src.cols/2);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;

            index++;
            cont_cambios=0;

            for(int y=src.rows/2; y>1 ;y--)// trazado del radio inferior vertical
            {

                if(y==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y,src.cols/2);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y,src.cols/2))
                    {
                        pixel_ant=src.at<uchar>(y,src.cols/2);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            cont_cambios=0;
            index++;
            continue;
        }
        else if(m==0.00)
        {
            for(int x=0; x<src.cols/2-1 ;x++)// trazado del radio derecho
            {
                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(src.rows/2,x);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(src.rows/2,x))
                    {
                        pixel_ant=src.at<uchar>(src.rows/2,x);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            index++;
            cont_cambios=0;

            for(int x=src.cols/2; x<src.cols-1 ;x++)// trazado del radio izquierdo
            {
                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(src.rows/2,x);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(src.rows/2,x))
                    {
                        pixel_ant=src.at<uchar>(src.rows/2,x);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            cont_cambios=0;
            index++;

            continue;
        }
        else
        {
            m=tan(m);
            for(int x=0; x<src.cols/2-1 ;x++) // trazado de los radios del primer cuadrante
            {
                y=m*(x);
                if(abs(y)>src.rows/2-1)
                    break;
                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y+src.rows/2,x+src.cols/2);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y+src.rows/2,x+src.cols/2))
                    {
                        pixel_ant=src.at<uchar>(y+src.rows/2,x+src.cols/2);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            index++;
            cont_cambios=0;

            for(int x=0; x<src.cols/2-1 ;x++)// trazado de los radios del segundo cuadrante
            {
                y=(x)*(m);
                x_=src.cols/2-x;
                if(abs(y)>=src.rows/2-1)
                    break;


                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y+src.rows/2,x_);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y+src.rows/2,x_))
                    {
                        pixel_ant=src.at<uchar>(y+src.rows/2,x_);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }

            *(src_firma+index)=cont_cambios;
            index++;
            cont_cambios=0;

            for(int x=0; x<src.cols/2-1 ;x++)// trazado de los radios del tercer cuadrante
            {
                y=(x)*(m);
                x_=src.cols/2-x;


                y_=src.rows/2-y;
                if(abs(y)>=src.rows/2-1)
                    break;

                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y_,x_);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y_,x_))
                    {
                        pixel_ant=src.at<uchar>(y_,x_);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            index++;
            cont_cambios=0;


            for(int x=0; x<src.cols/2-1 ;x++)// trazado de los radios del cuarto cuadrante
            {
                y=m*(x);
                y_=src.rows/2-y;
                if(abs(y)>=src.rows/2-1)
                    break;

                if(x==0)// se toma el valor del pixel de inicio, como la imagen es binaria puede ser 0 o 255
                {
                    pixel_ant=src.at<uchar>(y_,x+src.cols/2);
                    pixel_init=pixel_ant;
                }
                else
                {
                    if(pixel_ant != src.at<uchar>(y_,x+src.cols/2))
                    {
                        pixel_ant=src.at<uchar>(y_,x+src.cols/2);
                        if(pixel_ant==pixel_init)
                            cont_cambios++;

                    }
                }
            }


            *(src_firma+index)=cont_cambios;
            index++;
            cont_cambios=0;
        }
    }
}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: rota imagen
***************************************************************************************************/
//correccion de la posicion

cv::Mat rotacion(cv::Mat src,double angle){

cv::Point2f src2(src.cols/2.0F, src.rows/2.0F);
cv::Mat rot_mat;


    rot_mat = getRotationMatrix2D(src2,angle, 1.0);

cv::Mat dstrot;
cv::warpAffine(src, dstrot, rot_mat, src.size(), cv::INTER_CUBIC,
               cv::BORDER_CONSTANT,
               cv::Scalar(0,0,0));//ROTACION

return dstrot;

}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Alinea las letras verticalmente
***************************************************************************************************/
cv::Mat fourierAlienation(cv::Mat img,double &correc)
{

    Fourier f;



    cv::Mat imgF;//imagen en frecuencia
    cv::Mat imgRotacion;//imagen para rotacion

    int tamanoVect=0;//numero de componentes frecuencia




    imgF=f.getFourier(img);//obtiene transformada de fourier


    //conversion imagen flotante a entera
    double minVal, maxVal;
    minMaxLoc(imgF, &minVal, &maxVal); //find minimum and maximum intensities
    imgF.convertTo(imgF, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    int a=0;

    Simage::Pixval(imgF,a,tamanoVect);//obtengo numero de componentes en frecuencia
    vector<double> posicionesX(tamanoVect);//posiciones X componentes frecuencia
    vector<double> posicionesY(tamanoVect);//posiciones Y componenetes frecuencia
    Simage::whitePix(imgF,posicionesX,posicionesY);//obtiene posiciones componentes frecuencia


    //Dibujo linea
    double* x = &posicionesX[0];
    double* y = &posicionesY[0];
     LinearRegression lr(x, y,tamanoVect);  // create with two arrays


      qDebug()<<(imgF.cols-1)*lr.b + lr.a;
      qDebug()<<(1)*lr.b + lr.a;
      imshow("sin regrecion",imgF);

      line(imgF,Point2f (1,(1)*lr.b + lr.a ), Point2f (imgF.cols-1,(imgF.cols-1)*lr.b + lr.a ), Scalar(255,255,255),1);
      imshow("regresion",imgF);

    //calculo angulo de correcion

      int angle=(atan(lr.b))*180/2*3.14;

      //correccion de la posicion



      cv::Point2f src_center(imgF.cols/2.0F, img.rows/2.0F);
      cv::Mat rot_mat;


          rot_mat = getRotationMatrix2D(src_center,angle/2, 1.0);
          correc=angle/2;

      cv::Mat dstrot;
      cv::warpAffine(img, dstrot, rot_mat, img.size(), cv::INTER_CUBIC,
                     cv::BORDER_CONSTANT,
                     cv::Scalar(255,255,255));//ROTACION

      return dstrot;


}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Segmenta los caracteres
***************************************************************************************************/

std::vector<cv::Mat> segmentacion(cv::Mat Corregida, int inicio, int final,cv::Mat dstrot,double correc, vector<int> &segmentacionx2,float angleROtH,cv::Mat imgROtY)
{
    //calculo integrales

    imshow("la que entra a fourier",Corregida);

    IntegralProy integral;
    vector<double> integral3;
    int contZonas=0;
    threshold(Corregida,Corregida,200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
    threshold(Corregida,Corregida,250,255,1);
    integral3=integral.integralX(Corregida);//integrales proyeccion Y

    //segmentacion de zonas

    bool borde=false;
    for(int i=0;i< integral3.size()-1;i++)
    {



        if(integral3[i]<10 && borde==false)
        {
            line(Corregida,Point2f (i,0), Point2f (i,Corregida.rows), Scalar(255,255,255),1);
            contZonas++;
            borde=true;
        }
       if(integral3[i]>10 && borde==true)
        {

            borde=false;
        }


    }

    imshow("Segmentacion",Corregida);
    waitKey(0);

    vector<int> segmentacionx(contZonas+2);
    vector<int> segmentaciony(contZonas+2);


    borde=false;
    contZonas=0;
           for(int i=0;i< integral3.size()-1;i++)
           {



               if(integral3[i]<10 && borde==false)
               {
                   line(Corregida,Point2f (i,0), Point2f (i,Corregida.rows), Scalar(255,255,255),1);
                   contZonas++;
                   segmentacionx[contZonas]=i;
                   borde=true;

               }
              if(integral3[i]>10 && borde==true)
               {

                   borde=false;
               }


           }


             segmentacionx[segmentacionx.size()-1]=Corregida.cols;
             segmentacionx2=segmentacionx;



//       ////////////////////////////////////////////////////////////////
//        //segmentacion de zonas

           vector<cv::Mat> letras(segmentacionx.size()+1);
           vector<cv::Mat> letras2(segmentacionx.size()+1);
           cv::Mat ultima;
           dstrot.copyTo(ultima);
           ultima=rotacion(ultima,correc);

//sin(correc)*pow(pow(Corregida.cols/2,2)+ pow(Corregida.rows/2,2),0.5)
//abs(inicio-tan(angleROtH)*abs(Corregida.cols/2-segmentacionx[i]))
           //-angleROtH- 180


           bool flag=false;

           for(int i=0;i<segmentacionx.size()-2;i++)
           {

               for(int k=0;k<ultima.rows;k++)
               {
                   if(imgROtY.at<uchar>(k,segmentacionx[i])==255)
                   {

                       segmentaciony[i]=k;
                       if(k>150)segmentaciony[i]=130;
                       flag=true;
                   }

               }


               if(flag==false)segmentaciony[i]=0;
               flag=false;
           }

           for(int i=0;i<segmentacionx.size()-2;i++)
           {

               qDebug()<<segmentaciony[i]<<" "<<Corregida.rows+15<<" "<<ultima.rows;
               letras2[i]=ultima(Rect(segmentacionx[i],segmentaciony[i]-1,segmentacionx[i+1]-segmentacionx[i],Corregida.rows+15));

           }



//         //letras segmentadas


          for(int i=0;i< letras.size()-3;i++)
          {

              if(letras2[i].data)
              {
                 //threshold(letras2[i],letras2[i],200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);

              }
          }

          return letras2;



}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Compara tamaños
***************************************************************************************************/
bool compareContourLength ( cv::Vec4i line1, cv::Vec4i line2 )//ordena de mayor longitud a menor con distancia euclidiana
{
  double i = fabs( pow(((line1[0]-line1[2])*(line1[0]-line1[2]))+((line1[1]-line1[3])*(line1[1]-line1[3])),0.5) );
  double j = fabs( pow(((line2[0]-line2[2])*(line2[0]-line2[2]))+(line2[1]-line2[3])*(line2[1]-line2[3]),0.5) );
  //qDebug()<< "distancia del primero"<< i<< "distancia del segundo"<< j<< "en la q voy";
  return ( i > j );
}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Discretiza la imagen
***************************************************************************************************/


void colorReduceEfficient(cv::Mat &image, int div)//para imagenes que no estan rellenas del todo
{
    int nl=image.rows;
    int nc=image.cols;

    if(image.isContinuous())
    {
        //then no padded pixels
        nc=nc*nl;
        nl=1;//it is now a 1D array
    }
    //this loop is executed only once in case of a continuous image
    for(int j=0; j<nl; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for(int i=0; i<nc; i++)
        {
            //process each pixel
            data[i]=data[i]/div*div +div/2;
            //end pixel processing
        }//end for
    }//end for

}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Discretiza la imagen
***************************************************************************************************/
cv::Mat correccionHorizontal(cv::Mat image,int &inicioR,int &finalR,cv::Mat &original,float &angleRot)
{

     IntegralProy integral;
    cv::Mat src_peq;
    image.copyTo(src_peq);
    cv::Mat _M_SE3x5=cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::Mat dst, color_dst,src;
    cv::Mat rot_mat;
    double angle=0;

    cv::resize(src_peq,src,cv::Size(round(3*src_peq.cols),round(3*src_peq.cols)),3,3);
    cv::threshold(src,dst,150,255,CV_THRESH_BINARY);
    Canny( dst, dst, 50, 200, 3 );
    cv::morphologyEx(dst,dst, CV_MOP_GRADIENT ,_M_SE3x5);
    cvtColor( dst, color_dst, CV_GRAY2BGR );


    std::vector<cv::Vec4i> lines;
    HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
    std::sort(lines.begin(), lines.end(),compareContourLength);//ordena los contornos por area de mayor a menor
    for( int i = 0; i < 1; i++ )
    {
        line( color_dst, cv::Point(lines[i][0], lines[i][1]),cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0+40*i,0+30*i,255), 3, 8 );


    }
    angle=180*atan2((lines[1][1]-lines[1][3]),(lines[1][0]-lines[1][2]))/CV_PI;


    cv::Point2f src_center(color_dst.cols/2.0F, color_dst.rows/2.0F);
    if(abs(angle)>120)
    {

        rot_mat = getRotationMatrix2D(src_center,angle-180  , 1.0);
    }

    else if(abs(angle)<120&&abs(angle)>50)
    {
        rot_mat = getRotationMatrix2D(src_center,angle-80  , 1.0);

    }

    cv::Mat dstrot;
    angleRot=angle;
    cv::warpAffine(src, dstrot, rot_mat, color_dst.size());//ROTACION horizontal

    cv::Mat img;
    cv::Mat img2;
    cv::Mat img3;

    cv::cvtColor(dstrot,img2,CV_BGR2GRAY);
    //cvtColor(img2,img3,CV_GRAY2BGR);
    cv::Mat fragmentoHorizontal;
    colorReduceEfficient(img2,64);
   // imshow("discretizada",img2);
    equalizeHist(img2,img2);
    threshold(img2,img,200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
    threshold(img,img,220,255,1);

   vector<double> integralsline;
    vector<double> integrals;//integralesen direccion Y
    vector<double> integrals2;//integralesen direccion X
    int cambios[3];
    int  picos=0;
    int  picosX=0;


//    //calculo integrales
    integrals=integral.integralY(img);//integrales proyeccion X
    integralsline=integral.integralYline(img);//integrales proyeccion X

    int prom=0;

    //Calculo promedio

    for(int i=0;i< integrals.size()-1;i++)//calcula el promedio de cambios verticales por placa
     {
        prom+=integralsline[i];
    }

    prom=prom/integrals.size();

    //Segmentacion de zona

   for(int i=0;i< integrals.size()-1;i++)
    {
       if(integralsline[i]>prom)
       {
           line(img,Point2f (0,i), Point2f (img.cols-1,i), Scalar(255,255,255),3);
           integralsline[i]=1;

       }else{

           integralsline[i]=0;

       }


    }

   cv::Mat imageROI;
   bool area=false;
   bool zona=false;
   bool guarde=false;
   int tamano=0;
   int masgrande=0;
   int inicio=0;
   int inicioTemp=0;
   int final=0;

   for(int i=2;i< integrals.size()-1;i++)
    {

        if(integralsline[i]>0 && integralsline[i-1]>0)
        {
            tamano++;
            if(zona==false)area=true;
            zona=true;
         }

            if(zona==true && integralsline[i]<1)
            {
                if(tamano>masgrande)
                {
                    masgrande=tamano;
                    tamano=0;
                    final=i;
                    inicio=inicioTemp;
                }

             }


        if(integralsline[i]<1)
        {

            zona=false;
        }

        if(area==true && integralsline[i-2]<1){
            inicioTemp=i;
            area==false;

        }

    }

   qDebug()<<"inicio:"<<inicio;
   qDebug()<<"final:"<<final;

   imageROI=dstrot(Rect(0,inicio-10,img.cols,final-inicio + 10));//obtiene area de interes HORIZONTAL
   imshow("segmentacion Horizontal",dstrot);
   inicioR=inicio;
   finalR=final;
   original=dstrot;


    return imageROI;


}


void MainWindow::on_pushButton_clicked()
{
    octave_value_list arg_eval_out,arg_eval_in;

    arg_eval_in(0)= octave_value(2.9713e+04);
    arg_eval_in(1)= octave_value(-4.7374e+02);
    arg_eval_in(2)= octave_value(2.0051e+03);
    arg_eval_in(3)= octave_value(-2.6149e+03);
    arg_eval_in(4)= octave_value(3.2272e+03);
    arg_eval_in(5)= octave_value(-8.1204e+03);
    arg_eval_in(6)= octave_value(3.1763e+03);
    arg_eval_in(7)= octave_value(3.0177e+03);
    arg_eval_in(8)= octave_value(2.4687e+03);
    arg_eval_in(9)= octave_value(-1.4006e+03);
    arg_eval_in(10)= octave_value(2.4377e+03);
    arg_eval_in(11)= octave_value(6.8578e+02);
    arg_eval_in(12)= octave_value(-8.0483e+02);
    arg_eval_in(13)= octave_value(-1.2209e+03);
    arg_eval_in(14)= octave_value(-9.5363e+02);
    arg_eval_in(15)= octave_value(-5.8240e+02);
    arg_eval_in(16)= octave_value(-8.5046e+02);
    arg_eval_in(17)= octave_value(2.5811e+02);
    arg_eval_in(18)= octave_value(1.0936e+03);
    arg_eval_in(19)= octave_value(1.3279e+02);

    arg_eval_out=feval("eval_net_placas",arg_eval_in);
    qDebug()<<"clase"<<arg_eval_out(0).int_value();

}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion:Carga una imagen de un archivo al programa
***************************************************************************************************/

void MainWindow::on_pushButton_2_clicked()
{

    //ABRE VENTANA CARGA ARCHIVO
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), ".",
    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    image= cv::imread(fileName.toAscii().data());

    //MUESTRA IMAGEN EN INTERFAZ
    QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,image.step,QImage::Format_RGB888);//extrae imagen
    ui->label->setPixmap(QPixmap::fromImage(img));//muestra en label el video

}

void MainWindow::on_pushButton_3_clicked()//extraer
{
    cv::Mat original,originalGray,imgCorreccionHori;
    int inicio,final;
    cv::Mat imageROI2;
    vector<int> segmentacionx2;
     Ssobel dir;
    QString textoPlaca;
    QString  letra;
     CvANN_MLP net;
     CvANN_MLP netLetras;
     float angleROtH=0;


     net.load("/home/lex/Cv/QT/OCR_inteligencia/mlpNumeros.xml",0);
     netLetras.load("/home/lex/Cv/QT/OCR_inteligencia/mlpletras1%.xml",0);


    cv::Mat imageROI=correccionHorizontal(image,inicio,final,original,angleROtH);//segmenta horizontalmente la placa
     int mitad=original.cols/2;
    cv::cvtColor(imageROI,imageROI2,CV_BGR2GRAY);
    cv::cvtColor(original,originalGray,CV_BGR2GRAY);

    double correc=0;//angulo de correccion horizontal

   original.copyTo(imgCorreccionHori);


   cv::Mat imgCorreccionHori2;
   cv::cvtColor(imgCorreccionHori,imgCorreccionHori2,CV_BGR2GRAY);

for(int k=0;k<imgCorreccionHori2.rows;k++)

   {

        for(int i=0;i<imgCorreccionHori2.cols;i++)
       {

            if(imgCorreccionHori2.at<uchar>(k,i)>10)
           imgCorreccionHori2.at<uchar>(k,i)=imgCorreccionHori2.at<uchar>(k,i)-5;

       }
   }


    //line(imgCorreccionHori2,Point2f ( 0,inicio-10), Point2f (imgCorreccionHori.cols,inicio-10), Scalar(255,255,255),3);

    imgCorreccionHori2=rotacion(imgCorreccionHori2,-angleROtH- 180);

    line(imgCorreccionHori2,Point2f ( 0,inicio-10+(tan(((-angleROtH- 180)*3.1415)/180)*imgCorreccionHori2.cols)/2), Point2f (imgCorreccionHori.cols,inicio-10-(tan(((-angleROtH- 180)*3.1415)/180)*imgCorreccionHori2.cols)/2), Scalar(256,256,256),3);


    imshow("imagen con linea",imgCorreccionHori2);

//   inicio-10- tan(-angleROtH- 180)*(imgCorreccionHori.cols/2)

//   inicio-10 + tan(-angleROtH- 180)*(imgCorreccionHori.cols/2)

//          2*tan(-angleROtH- 180)*(imgCorreccionHori.cols/2)

          // angleROtH=asin((2*tan(-angleROtH- 180)*(imgCorreccionHori.cols/2))/pow(pow(2*tan(-angleROtH- 180)*(imgCorreccionHori.cols/2),2)+ pow(imgCorreccionHori.cols,2),0.5 ));




    cv::Mat Corregida=fourierAlienation(imageROI2,correc);//alinea verticalmente
    std::vector<cv::Mat> letras2=segmentacion(Corregida,inicio,final,originalGray,correc,segmentacionx2,angleROtH,imgCorreccionHori2);//segmenta los caracteres


   //////////Extraccion Caracteristicas//////////


    vector<double> caracteristicas(3843);

    int contCaract=0;

    int PosCaracter=0;

             for( int i=0;i< letras2.size()-2;i++)
             {
                 contCaract=0;


                 if(letras2[i].data)
                 {


                    // threshold(letras2[i],letras2[i],200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
                    //imshow("letra7", letras2[i]);



                     cv::Mat img3;

                     threshold(letras2[i],img3,200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
                     threshold(img3,img3,250,255,1);


                     Hog H_featHog;
                     vector<float> b;
                     int Xresize=15;//tamaño en x de la imagen con cambio de tamaño
                     int Yresize=30; //tamaño en y de la imagen con cambio de tamaño

                     ////INICIA HOG//////
                         int iter2=0;



                         b=H_featHog.getHOG(letras2[i],Size (64,128), Size (8,8));



                        std::vector<float>::iterator itc=H_featHog.descriptorsValues.begin();
                        int ab=0;


                                    while(ab<b.size())
                                    {

                                       caracteristicas[contCaract]=b[ab];
                                      // qDebug()<<b[ab];


                                        ab++;
                                        contCaract++;
                                    }


                      ///INTEGRALES DE PROTECCION//
                         cv::Mat img2;

                       cv::resize(img3,img2, Size(Xresize,Yresize) );


                       IntegralProy integral;




                       vector<double> c;
                       vector<double> d;

                       c=integral.integralX(img2);
                       d=integral.integralY(img2);




                       for(int iter2=0;iter2<Xresize ;iter2++)// integrales de proyeccion en x
                       {
                           caracteristicas[contCaract]=c[iter2];
                           contCaract++;
                       }




                       for(int iter2=0;iter2<Yresize ;iter2++)// integrales de proyeccion en y
                       {
                           caracteristicas[contCaract]=d[iter2];
                           contCaract++;
                       }

                        int cuenta=contCaract;

                       ///INICIA FIRMA///
                       cv::Mat dst,src;

                       cv::resize(letras2[i],src,cv::Size(round(6*letras2[i].cols),round(3*letras2[i].cols)),3,3);
                       cv::threshold(src,dst,150,255,CV_THRESH_BINARY);
                       Canny( dst, dst, 50, 200, 3 );

                       int num_lines=3;
                       int src_firma[(num_lines+1)*4];

                       get_firma_binary_changes(dst,3,src_firma);



                       //double a=(double)src_firma;
//                       int a = (int)*src_firma;
//                       double z = (double) src_firma[i];


                       for(int i=cuenta;i<caracteristicas.size();i++)
                       {
                       //double z = (double) src_firma[i-contCaract];
                       caracteristicas[i]=src_firma[i-cuenta];
                       contCaract++;
                       }


                        caracteristicas[caracteristicas.size()-2]=dir.getVerticalC(letras2[i],190);
                        contCaract++;
                       caracteristicas[caracteristicas.size()-1]=dir.getHorizontalC(letras2[i],190);

                       ///////////////////////////////////////////////////////////////////////
                       ////////////////////EVALUACION RED NEURONAL///////////////////////////////
                        bool esLetra=true;

                        cv::Mat in(1,3843, CV_32FC1 );//crea la matriz con las caracteristicas deseadas

                        for(int i=0;i<caracteristicas.size()-1;i++)
                        {
                            in.at<float>(0,i)=caracteristicas[i];

                        }



//                        for(int i=0;i<caracteristicas.size()-1;i++)
//                                        {
//                                             qDebug()<<i<<" "<<in.at<float>(0,i);

//                                        }




                        if(( segmentacionx2[i]-PosCaracter>20)  && segmentacionx2[i]>=mitad)
                        {
                            cv::Mat output(1,10,CV_32FC1);
                            net.predict(in,output);//calcula la salida de la red
                            cv::Point maxLoc;//ubicacion del valor maximo
                            double maxVal;//valor maximo de la salida
                            minMaxLoc(output,0,&maxVal,0,&maxLoc);//halla el maximo
                            qDebug()<<"clase: "<<maxLoc.x;//retorna la posicion del maximo
                            letra= QString::number(maxLoc.x);//lleva el numero de carpeta
                         }


                        else
                        {
                            cv::Mat output(1,26,CV_32FC1);
                            netLetras.predict(in,output);//calcula la salida de la red
                            cv::Point maxLoc;//ubicacion del valor maximo
                            double maxVal;//valor maximo de la salida
                            minMaxLoc(output,0,&maxVal,0,&maxLoc);//halla el maximo
                            ui->label_2->setText("someText");
                            letra= QString::number(maxLoc.x);//lleva el numero de carpeta


                           switch(maxLoc.x+1)
                           {

                                case 1:
                               qDebug()<<"clase:  A";
                               letra= "A";//lleva el numero de carpeta
                               break;
                                case 2:
                               qDebug()<<"clase:  B";
                             letra="B";//lleva el numero de carpeta
                               break;
                                case 3:
                              qDebug()<<"clase:  C";
                              letra= "C";//lleva el numero de carpeta
                               break;
                                case 4:
                               qDebug()<<"clase:  D";
                               letra= "D";//lleva el numero de carpeta
                               break;
                                case 5:
                                                              qDebug()<<"clase:  E";
                                                              letra="E";//lleva el numero de carpeta
                               break;
                                case 6:
                                                        qDebug()<<"clase:  F";
                                                         letra="F";//lleva el numero de carpeta
                               break;
                               case 7:
                                                         qDebug()<<"clase:  G";
                               letra="G";
                               break;

                               case 8:
                                                              qDebug()<<"clase:  H";
                              letra="H";
                               break;
                               case 9:
                                                         qDebug()<<"clase:  I";
                                letra="I";
                               break;
                               case 10:
                                                         qDebug()<<"clase:  J";
                               letra="J";
                               break;
                               case 11:
                                                              qDebug()<<"clase:  K";
                               letra="K";
                               break;
                               case 12:
                                                         qDebug()<<"clase:  L";
                                letra="L";
                               break;
                               case 13:
                                                         qDebug()<<"clase:  M";
                               letra="M";
                               break;
                                case 14:
                                                              qDebug()<<"clase:  N";
                             letra="N";
                               break;
                                case 15:
                                                         qDebug()<<"clase:  O";
                                letra="O";
                               break;
                               case 16:
                                                             qDebug()<<"clase:  P";
                               letra="P";
                               break;
                               case 17:
                                                                  qDebug()<<"clase:  Q";
                                letra="Q";
                               break;
                               case 18:
                                                             qDebug()<<"clase:  R";
                               letra="R";
                               break;
                               case 19:segmentacionx2[i];
                                                             qDebug()<<"clase:  S";
                                letra="S";
                               break;
                               case 20:
                                                                  qDebug()<<"clase:  T";
                               letra="T";
                               break;
                               case 21:
                                                             qDebug()<<"clase:  U";
                               letra="U";
                               break;
                               case 22:
                                                             qDebug()<<"clase:  V";
                               letra="V";
                               break;
                               case 23:
                                                                  qDebug()<<"clase:  W";
                              letra="W";
                               break;
                               case 24:
                                                             qDebug()<<"clase:  X";
                               letra="X";
                               break;
                               case 25:
                                                                  qDebug()<<"clase:  Y";
                               letra="Y";
                               break;
                               case 26:
                                                             qDebug()<<"clase:  Z";
                                letra="Z";
                               break;

                           }
                         }


                        PosCaracter=segmentacionx2[i];

                            imshow("imagen Procesando",letras2[i]);
                            textoPlaca=textoPlaca + letra;
                            ui->label_2->setText(textoPlaca);
                             waitKey(0);


//                        arma::mat caracteristicasMatriz;
//                        arma::mat resultadoParaLaRed;
//                        caracteristicasMatriz=caracteristicas;
//                        arma::mat caracteristicasMatriz2=caracteristicasMatriz.t();

//                        qDebug()<<"Proyeccion MATRIZ:";
//                        for(int j=cuenta ;j<cuenta+ 10;j++)
//                            qDebug()<<caracteristicasMatriz(j)<<" "<<src_firma[j-cuenta]<<" "<<j-(cuenta);





//                        qDebug()<<"filas letra"<<caracteristicasMatriz2.n_rows;
//                        qDebug()<<"columnas letra"<<caracteristicasMatriz2.n_cols;
//                        qDebug()<<"filas reduccion"<<matrizReduccion.n_rows;
//                        qDebug()<<"columnas reduccion"<<matrizReduccion.n_cols;


//                        qDebug()<<"Ultimas caracteristicas"<<caracteristicas[caracteristicas.size()-2];


//                       resultadoParaLaRed=(caracteristicasMatriz2*matrizReduccion);

//                       //primero red que separa basura para cambiar la bandera esLetra

//                       qDebug()<<"Posicion en la placa"<<segmentacionx2[i];
//                       qDebug()<<"Mitad de la placa"<<mitad;
//                        imshow("imagen Procesando",letras2[i]);
//                        waitKey(0);

//                       //entra en la red de letras
//                       if((segmentacionx2[i]<mitad) )
//                       {
//                           octave_value_list arg_eval_out,arg_eval_in;

//                           arg_eval_in(0)= octave_value(&resultadoParaLaRed);
////                           arg_eval_in(1)= octave_value(resultadoParaLaRed(1));
////                           arg_eval_in(2)= octave_value(resultadoParaLaRed(2));
////                           arg_eval_in(3)= octave_value(resultadoParaLaRed(3));
////                           arg_eval_in(4)= octave_value(resultadoParaLaRed(4));
////                           arg_eval_in(5)= octave_value(resultadoParaLaRed(5));
////                           arg_eval_in(6)= octave_value(resultadoParaLaRed(6));
////                           arg_eval_in(7)= octave_value(resultadoParaLaRed(7));
////                           arg_eval_in(8)= octave_value(resultadoParaLaRed(8));
////                           arg_eval_in(9)= octave_value(resultadoParaLaRed(9));
////                           arg_eval_in(10)= octave_value(resultadoParaLaRed(10));
////                           arg_eval_in(11)= octave_value(resultadoParaLaRed(11));
////                           arg_eval_in(12)= octave_value(resultadoParaLaRed(12));
////                           arg_eval_in(13)= octave_value(resultadoParaLaRed(13));
////                           arg_eval_in(14)= octave_value(resultadoParaLaRed(14));
////                           arg_eval_in(15)= octave_value(resultadoParaLaRed(15));
////                           arg_eval_in(16)= octave_value(resultadoParaLaRed(16));
////                           arg_eval_in(17)= octave_value(resultadoParaLaRed(17));
////                           arg_eval_in(18)= octave_value(resultadoParaLaRed(18));
////                           arg_eval_in(19)= octave_value(resultadoParaLaRed(19));

//                           arg_eval_out=feval("eval_net_letras",arg_eval_in);


//                           switch(arg_eval_out(0).int_value())
//                           {

//                                case 1:
//                               qDebug()<<"clase:  A"; break;
//                                case 2:
//                               qDebug()<<"clase:  B"; break;
//                                case 3:
//                                                         qDebug()<<"clase:  C"; break;
//                                case 4:
//                                                         qDebug()<<"clase:  D"; break;
//                                case 5:
//                                                              qDebug()<<"clase:  E"; break;
//                                case 6:
//                                                        qDebug()<<"clase:  F"; break;
//                               case 7:
//                                                         qDebug()<<"clase:  G"; break;

//                               case 8:
//                                                              qDebug()<<"clase:  H"; break;
//                               case 9:
//                                                         qDebug()<<"clase:  I"; break;
//                               case 10:
//                                                         qDebug()<<"clase:  J"; break;
//                               case 11:
//                                                              qDebug()<<"clase:  K"; break;
//                               case 12:
//                                                         qDebug()<<"clase:  L"; break;
//                               case 13:
//                                                         qDebug()<<"clase:  M"; break;
//                                case 14:
//                                                              qDebug()<<"clase:  N"; break;
//                                case 15:
//                                                         qDebug()<<"clase:  O"; break;
//                           case 16:
//                                                         qDebug()<<"clase:  P"; break;
//                           case 17:
//                                                              qDebug()<<"clase:  Q"; break;
//                           case 18:
//                                                         qDebug()<<"clase:  R"; break;
//                           case 19:
//                                                         qDebug()<<"clase:  S"; break;
//                           case 20:
//                                                              qDebug()<<"clase:  T"; break;
//                           case 21:
//                                                         qDebug()<<"clase:  U"; break;
//                           case 22:
//                                                         qDebug()<<"clase:  V"; break;
//                           case 23:
//                                                              qDebug()<<"clase:  W"; break;
//                           case 24:
//                                                         qDebug()<<"clase:  X"; break;
//                           case 25:
//                                                              qDebug()<<"clase:  Y"; break;
//                           case 26:
//                                                         qDebug()<<"clase:  Z"; break;

//                           }

                     //  }

//                       //entra en la red de numeros
//                       if((segmentacionx2[i]>=mitad-20) )
//                       {

//                           octave_value_list arg_eval_out,arg_eval_in;



//                           arg_eval_out=feval("eval_net_placas",arg_eval_in);

//                           switch(arg_eval_out(0).int_value())
//                           {

//                                case 1:
//                               qDebug()<<"clase:  0"; break;
//                                case 2:
//                               qDebug()<<"clase:  1"; break;
//                                case 3:
//                          qDebug()<<"clase:  2"; break;
//                                case 4:
//                          qDebug()<<"clase:  3"; break;
//                                case 5:
//                               qDebug()<<"clase:  4"; break;
//                                case 6:
//                          qDebug()<<"clase:  5"; break;
//                               case 7:
//                          qDebug()<<"clase:  6"; break;
//                               case 8:
//                               qDebug()<<"clase:  7"; break;
//                               case 9:
//                          qDebug()<<"clase:  8"; break;
//                               case 10:
//                               qDebug()<<"clase:  9"; break;
//                           }

//                       }




                         contCaract=0;



//                         qDebug()<<"LETRA #:"<< i;
//                         for(int i=0;i<b.size();i++)
//                             cout<<caracteristicas[i]<<" ";

//                         qDebug()<<"HOG:"<< i;

//                         for(int i=0;i<b.size();i++)
//                             qDebug()<<b[i]<<" ";
//                         cv::waitKey(0);
//                         imshow("cual",original);


                   }

                }

//             for(int i=0;i<caracteristicas.size();i++)
//                 cout<<caracteristicas[i]<<" ";





}
