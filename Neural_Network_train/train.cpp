#include "train.h"
#include "ui_train.h"

Train::Train(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Train)
{
    ui->setupUi(this);
}

Train::~Train()
{
    delete ui;
}


/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: ingresa comando a consola y devuelve la respuesta

***************************************************************************************************/

QString consolesAsk(std::string command) {

    QProcess sh;
    sh.start("sh", QStringList() << "-c" << command.c_str());
    sh.waitForFinished();
    QByteArray out = sh.readAll();
    QString salida(out);
     sh.close();
    return salida;
}




/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion: Extrae la firma de la imagen

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
Descripcion:Al presionar el boton Extraer

***************************************************************************************************/
void Train::on_pushButton_clicked()
{
    int numero_de_placas_base=299;
    int numeroMuestras=2367;
    int Xresize=15;//tamaño en x de la imagen con cambio de tamaño
    int Yresize=30; //tamaño en y de la imagen con cambio de tamaño


    QString path;
       QString pathPrueba;
       QString pathImages;
       QString pathImagesPrueba;
       QString pathConsole;
       int contOut=-1;
       int contOutPrueba=-1;


       cv::Mat inPrueba(400,3843, CV_32FC1 );//crea la matriz para error de prueba

     cv::Mat in(5200,3843, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
     //cv::Mat inPrueba(300,3843, CV_32FC1 );//crea la matriz para error de prueba
     cv::Mat inProy(5200,45, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
     cv::Mat inHog(5200,3780, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
     cv::Mat inFirmas(5200,18, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
     cv::Mat inProFirm(5200,63, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
     path="/home/lex/Cv/Images/placasdatabaseEquilibrada/";
     pathPrueba="/home/lex/Cv/Images/placasdatabaseEquilibradaPrueba/";

//carpeta

    for(int carpeta=10;carpeta<36;carpeta++){

        QString  fold= QString::number(carpeta);//lleva el numero de carpeta

        pathImages= path + fold+ "/";
        pathConsole="cd " + path + fold + " && " +"ls | wc -l";//devuelve el nuemero de archivos en el directorio
        std::string utf8_text = pathConsole.toUtf8().constData();//conversion a cadena strings
        QString respuesta=consolesAsk(utf8_text);
        numero_de_placas_base=respuesta.toInt();//transforma string a entero


        //qDebug()<<numero_de_placas_base;




        Ssobel dir;


        //archivo
        for(int iter=1;iter<=numero_de_placas_base;iter++)//NUMERO DE LETRAS
        {

             pathImages= path + fold+ "/";
             pathImagesPrueba= pathPrueba + fold+ "/";
//            if(iter<10 && iter>0)
//                pathImages.append("000");
//            else if(iter<100 && iter>=10)
//                pathImages.append("00");
//            else if(iter<1000 && iter>=100)
//                pathImages.append("0");
            pathImages.append(QString("%1").arg(iter));
            pathImagesPrueba.append(QString("%1").arg(iter));
           // pathImages.append(".jpeg");
            //path<<(string)index;

             //qDebug()<<pathImages;


            cv::Mat img= cv::imread(pathImages.toStdString().c_str(), 1);// LA IMAGEN QUE VOY COGIENDO
            cv::Mat imgPrueba= cv::imread(pathImagesPrueba.toStdString().c_str(), 1);// LA IMAGEN QUE VOY COGIENDO



            //cout<<carpeta<<","<<contOut<<" ";
                        if(img.data)
                        {

                            contOut++;
                            //////////Extraccion Caracteristicas//////////

//                            if(imgPrueba.data)
//                            {
//                            imshow("imagen",imgPrueba);
//                            qDebug()<<contOutPrueba;
//                            waitKey(0);
//                            }


                             vector<float> caracteristicas(3843);
                             vector<float> caracteristicasPrueba(3843);
                             vector<float> intProyeccion(45);

                             int contCaract=0;
                             int contCaractPrueba=0;


                              Hog H_featHog;
                              vector<float> b;//Almacena los HOG
                              vector<float> bPrueba;//almacena los HOG
                              int Xresize=15;//tamaño en x de la imagen con cambio de tamaño
                              int Yresize=30; //tamaño en y de la imagen con cambio de tamaño

//                               if(imgPrueba.data)
//                               {
//                                   imshow("imagen Prueba",imgPrueba);
//                                   waitKey(0);
//                                }


                  ////INICIA HOG//////
                              int iter2=0;

                              cv::Mat img3;
                              cv::Mat img3Prueba;

                              cvtColor(img,img3,CV_BGR2GRAY);
                              if(imgPrueba.data){
                              cvtColor(imgPrueba,img3Prueba,CV_BGR2GRAY);
                              }


                              threshold(img3,img3,200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
                              threshold(img3,img3,250,255,1);


                              if(imgPrueba.data)
                              {
                                threshold(img3Prueba,img3Prueba,200,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
                                threshold(img3Prueba,img3Prueba,250,255,1);
                                contOutPrueba++;
                              }


                           b=H_featHog.getHOG(img,Size (64,128), Size (8,8));
                           if(imgPrueba.data)
                           bPrueba=H_featHog.getHOG(imgPrueba,Size (64,128), Size (8,8));



                           std::vector<float>::iterator itc=H_featHog.descriptorsValues.begin();
                           int ab=0;


                                       while(ab<b.size())
                                       {

                                          caracteristicas[contCaract]=b[ab];
                                          if(imgPrueba.data)
                                          {
                                            caracteristicasPrueba[contCaractPrueba]=bPrueba[ab];
                                            contCaractPrueba++;
                                          }


                                           ab++;
                                           contCaract++;
                                       }


                   ///INTEGRALES DE PROTECCION//
                            cv::Mat img2;
                           cv::Mat img2Prueba;

                          cv::resize(img3, img2, Size(Xresize,Yresize) );
                          if(imgPrueba.data)
                          cv::resize(imgPrueba, img2Prueba, Size(Xresize,Yresize) );



                          IntegralProy integral;



                          vector<double> c;
                          vector<double> d;
                          vector<double> cPrueba;
                          vector<double> dPrueba;

                          c=integral.integralX(img2);
                          d=integral.integralY(img2);
                          if(imgPrueba.data)
                          {
                          cPrueba=integral.integralX(img2Prueba);
                          dPrueba=integral.integralY(img2Prueba);
                          }



                          for(int iter2=0;iter2<Xresize ;iter2++)// integrales de proyeccion en x
                          {
                              caracteristicas[contCaract]=c[iter2];//ingreso a vector de todas
                              if(imgPrueba.data){
                              caracteristicasPrueba[contCaractPrueba]=cPrueba[iter2];//ingreso a vector de todas
                              contCaractPrueba++;
                              }
                              intProyeccion[iter2]=c[iter2];//ingreso a vector de integrales de proyeccion

                              contCaract++;
                          }




                          for(int iter2=0;iter2<Yresize ;iter2++)// integrales de proyeccion en y
                          {
                              caracteristicas[contCaract]=d[iter2];
                              if(imgPrueba.data){
                              caracteristicasPrueba[contCaractPrueba]=dPrueba[iter2];//ingreso a vector de todas
                              contCaractPrueba++;
                              }
                              intProyeccion[15+ iter2]=d[iter2];//ingreso a vector de integrales de proyeccion
                              contCaract++;


                          }


                                              int cuenta=contCaract;
                    ///INICIA FIRMA///
                                cv::Mat dst,src;
                              cv::Mat dstPrueba,srcPrueba;

                              cv::resize(img,src,cv::Size(round(6*img.cols),round(3*img.cols)),3,3);
                              if(imgPrueba.data)
                              cv::resize(imgPrueba,srcPrueba,cv::Size(round(6*img.cols),round(3*img.cols)),3,3);
                              cv::threshold(src,dst,150,255,CV_THRESH_BINARY);
                              if(imgPrueba.data)
                              cv::threshold(srcPrueba,dstPrueba,150,255,CV_THRESH_BINARY);
                              Canny( dst, dst, 50, 200, 3 );
                              if(imgPrueba.data)
                              Canny( dstPrueba, dstPrueba, 50, 200, 3 );

                              int num_lines=3;
                              int src_firma[(num_lines+1)*4];
                              int src_firmaPrueba[(num_lines+1)*4];

                              get_firma_binary_changes(dst,3,src_firma);
                              if(imgPrueba.data)
                              get_firma_binary_changes(dstPrueba,3,src_firmaPrueba);


                              for(int i=cuenta;i<caracteristicas.size();i++)
                              {
                                //double z = (double) src_firma[i-contCaract];
                                caracteristicas[i]=src_firma[i-cuenta];
                                if(imgPrueba.data)
                                caracteristicasPrueba[i]=src_firmaPrueba[i-cuenta];
                                contCaract++;
                              }



                               caracteristicas[caracteristicas.size()-2]=dir.getVerticalC(img,190);
                               if(imgPrueba.data){
                               caracteristicasPrueba[caracteristicasPrueba.size()-2]=dir.getVerticalC(imgPrueba,190);
                               contCaractPrueba++;
                               }
                               contCaract++;
                              caracteristicas[caracteristicas.size()-1]=dir.getHorizontalC(img,190);
                              if(imgPrueba.data)
                              {
                              caracteristicasPrueba[caracteristicasPrueba.size()-1]=dir.getHorizontalC(imgPrueba,190);
                              contCaractPrueba++;
                               }








                    //Extraccion para todas
                              for(int i=0;i<caracteristicas.size()-1;i++)
                              {
                                  in.at<float>(contOut,i)=caracteristicas[i];





                                  if(contOutPrueba<400 && imgPrueba.data){
                                     inPrueba.at<float>(contOutPrueba,i)=caracteristicasPrueba[i];


                                  }


                                  if(i>3779)
                                  {
                                       inProFirm.at<float>(contOut,i- 3780)=caracteristicas[i];

                                  }

                                  if(i<3780)
                                  {
                                      inHog.at<float>(contOut,i)=caracteristicas[i];
                                  }

                                  if(i>caracteristicas.size()-19)
                                  {
                                      inFirmas.at<float>(contOut,i- caracteristicas.size()-18)=caracteristicas[i];

                                  }


                              }


                    //Extraccion para integrales
                    for(int i=0;i<45;i++)
                    {
                        inProy.at<float>(contOut,i)=intProyeccion[i];


                    }




            }


        }


    }
    //verificacion de que se escribio






    // se creaMatriz de salida esperada

       int num_clases=26;
       int indiv_por_clase=200;
       int indiv_por_clasePrueba=16;

       cv::Mat out(num_clases*indiv_por_clase,num_clases, CV_32FC1 );//crea la matriz con las caracteristicas deseadas
       cv::Mat outPrueba(num_clases*indiv_por_clasePrueba,num_clases, CV_32FC1 );//crea la matriz con las caracteristicas deseadas

    for(int i=0;i<out.rows;i++)
    {
        int auxiliar_classes= i/indiv_por_clase;

        for(int k=0;k<out.cols;k++)
        {
            if(k==auxiliar_classes)
            {
                out.at<float>(i,k)=1;
            }
            else
            {
                out.at<float>(i,k)=0;
            }
        }
    }

    for(int i=0;i<outPrueba.rows;i++)
       {
           int auxiliar_classes= i/indiv_por_clasePrueba;

           for(int k=0;k<outPrueba.cols;k++)
           {
               if(k==auxiliar_classes)
               {
                   outPrueba.at<float>(i,k)=1;
               }
               else
               {
                   outPrueba.at<float>(i,k)=0;
               }
           }
       }



    //////////////////////////////Entrenamiento/////////////////////////////////
     qDebug()<<"Entrenando...";


//     for(int j=3700; j<3843; j++)
//     {

//        qDebug()<<j<<" "<<inPrueba.at<float>(300,j)<<" ";
//     }

//     waitKey(0);

     net.train(in,out,100,26);
      qDebug()<<"voy a calcular el error";

     int marcador=0;
     float error=0;

     /////CALCULO ERROR ENTRENAMIENTO
      qDebug()<<"Evaluando error de entrenamiento...";

     for(int l=0;l<5200;l++)
     {

          cv::Mat in2(1,3843, CV_32FC1 );//crea la matriz con las caracteristicas deseadas


         for(int k=0;k<3843;k++)
         {


              in2.at<float>(0,k)= in.at<float>(l,k);//------------------------------------->ACA

         }


        marcador=l/200;





        cv::Mat output(1,26,CV_32FC1);
        net.ann.predict(in2,output);//calcula la salida de la red
        cv::Point maxLoc;//ubicacion del valor maximo
        double maxVal;//valor maximo de la salida
        minMaxLoc(output,0,&maxVal,0,&maxLoc);//halla el maximo

       //qDebug()<<"clase: "<<maxLoc.x ;//retorna la posicion del maximo



       if(maxLoc.x!=marcador)error++;



    }

    float error2=error/5200;
    qDebug()<<"Error entrenamiento ="<<error2;
    error=0;
    error2=0;


    /////CALCULO ERROR PRUEBA
     qDebug()<<"Evaluando error prueba...";

    for(int l=0;l<400;l++)
    {

         cv::Mat in2(1,3843, CV_32FC1 );//crea la matriz con las caracteristicas deseadas


        for(int k=0;k<3843;k++)
        {


             in2.at<float>(0,k)= inPrueba.at<float>(l,k);//------------------------------------->ACA

        }

        marcador=l/16;

        cv::Mat output(1,26,CV_32FC1);
        net.ann.predict(in2,output);//calcula la salida de la red
        cv::Point maxLoc;//ubicacion del valor maximo
        double maxVal;//valor maximo de la salida
        minMaxLoc(output,0,&maxVal,0,&maxLoc);//halla el maximo


       if(maxLoc.x!=marcador)error++;


    }

    error2=error/400;
    qDebug()<<"Error Prueba ="<<error2;
    //net.evalNet()


//    for(int i=0;i< 300; i++)
//    {
//        for(int j=0; j<3843; j++)
//        {

//           qDebug()<<inPrueba.at<float>(i,j)<<" ";
//        }

//        qDebug()<<i<<"////////////";
//    }

    waitKey(0);


}

/***************************************************************************************************
Metodos
Autor: Alexander Gómez villa - Sebastian Guzman Obando - German Diez Valencia
Descripcion:Al presionar el boton Entrenar

***************************************************************************************************/



void Train::on_pushButton_2_clicked()
{


}
