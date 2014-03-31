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

#include "procesamiento.h"
#include<QDebug>

/*
 * Constructor por defecto
 */
Procesamiento::Procesamiento(QObject *parent) :
    QObject(parent)
{
}

//*********************************************************************************************************************
/*
 * Constructor de copia, se encarga de copiar todos los valores de los atributos de otro objeto del mismo tipo
 */
Procesamiento::Procesamiento(Procesamiento* toCopy)
{
    signal=toCopy->signal;
    clean=toCopy->clean;
    Fs=toCopy->Fs;
    bitRate=toCopy->bitRate;
    iRatio=toCopy->iRatio;
    fRatio=toCopy->fRatio;
    signalName=toCopy->signalName;
}

//*********************************************************************************************************************
/*
 * Destructor
 */
Procesamiento::~Procesamiento()
{
    delete player; // Libera memoria dinamica
}

//*********************************************************************************************************************

/*
* Carga una senal de un archivo .wav a la memoria
*/

void Procesamiento::openSignal(char *fileName)
{
    signalName=fileName; // Mantener el nombre del archivo en la memoria

    octave_value_list filenameOct, sigInfo; // Declarar argumentos para cargar el archivo desde octave

    filenameOct=octave_value(fileName); // Como argumento de entrada el nombre del archivo de la senal

    sigInfo=feval("wavread",filenameOct,3); // Llamar a wavread

    // Llevar a matrices los valores devueltos por wavread

    signal = sigInfo(0).matrix_value();
    Fs = sigInfo(1).matrix_value();;
    bitRate = sigInfo(2).matrix_value();

}

//*********************************************************************************************************************

/*
 * Reproduce un la senal original
 */
void Procesamiento::playSignal()
{
    player=new QProcess(); // Reserva memoria dinamica para el objeto que llama al proceso

    // Conectar la senal de finalizacion del proceso con el slot que termina la reproduccion
    connect(player,SIGNAL(finished(int)),this,SLOT(playEnded()));

    // Iniciar el proceso paplay que reproduce la senal en el archivo de la senal original
    player->start(QString("paplay ")+ "\""+signalName+ "\"");

    if (!player->waitForStarted()){ // Si no se pudo iniciar el proceso
        // playFailed();
        return; // Regresar
    }

    playFlag=true; // Bandera que indica que se esta reproduciendo una senal

}

//*********************************************************************************************************************

/*
 * Reproduce la senal limpia
 */

void Procesamiento::playClean()
{
    octave_value_list argOut; // Declarar argumentos para escribir la senal a reproducir en un archivo temporal

    // Llenar los argumentos con la informacion de la senal limpia y el nombre de archivo
    argOut(0)=octave_value(clean);
    argOut(1)=octave_value(Fs);
    argOut(2)=octave_value(bitRate);
    argOut(3)=octave_value("Temp.wav");

    feval("wavwrite",argOut,0); // Escribir el archivo temporal por medio de la funcion wavwrite de Octave
    tempFlag=true; // Bandera para indicar que se ha escrito un archivo temporal

    player=new QProcess(); // Reserva memoria dinamica para el objeto que llama al proceso

    // Conectar la senal de finalizacion del proceso con el slot que termina la reproduccion
    connect(player,SIGNAL(finished(int)),this,SLOT(playEnded()));

    // Iniciar el proceso paplay que reproduce la senal en el archivo temporal
    player->start(QString("paplay Temp.wav"));

    if (!player->waitForStarted()){ // Si no se pudo iniciar el proceso
        // playFailed();
        return; // regresar
    }

    playFlag=true; // Bandera que indica que se esta reproduciendo una senal


}

//*********************************************************************************************************************

/*
 * Reproduce un fragmento, indicado por el usuario, de la senal original
 */
void Procesamiento::playSegment()
{
    // Calcular muestra inicial y final de la reproduccion
    long inicial = signal.rows()*iRatio;
    long final = signal.rows()*fRatio;

    octave_value_list argOut; // Declarar argumentos para escribir la senal a reproducir en un archivo temporal

    // Llenar los argumentos con la informacion del fragmento de senal y el nombre de archivo
    argOut(0)=octave_value(signal.extract(octave_idx_type(inicial), octave_idx_type(0),octave_idx_type(final),octave_idx_type(0)));
    argOut(1)=octave_value(Fs);
    argOut(2)=octave_value(bitRate);
    argOut(3)=octave_value("Temp.wav");

    feval("wavwrite",argOut,0); // Escribir el archivo temporar por medio de la funcion wavwrite de Octave
    tempFlag=true; // Bandera para indicar que se ha escrito un archivo temporal

    player=new QProcess(); // Reserva memoria dinamica para el objeto que llama al proceso

     // Conectar la senal de finalizacion del proceso con el slot que termina la reproduccion
    connect(player,SIGNAL(finished(int)),this,SLOT(playEnded()));

    // Iniciar el proceso paplay que reproduce la senal en el archivo temporal
    player->start(QString("paplay Temp.wav"));

    if (!player->waitForStarted()){  // Si no se pudo iniciar el proceso
        // playFailed();
        return;
    }

    playFlag=true; // Bandera que indica que se esta reproduciendo una senal



}

//*********************************************************************************************************************
/*
 * Reproduce un fragmento, indicado por el usuario, de la senal limpia
 */
void Procesamiento::playCleanSegment()
{
    // Calcular muestra inicial y final de la reproduccion
    long inicial = clean.rows()*iRatio;
    long final = clean.rows()*fRatio;

    octave_value_list argOut; // Declarar argumentos para escribir la senal a reproducir en un archivo temporal

    // Llenar los argumentos con la informacion del fragmento de senal y el nombre de archivo
    argOut(0)=octave_value(clean.extract(octave_idx_type(inicial), octave_idx_type(0),octave_idx_type(final),octave_idx_type(0)));
    argOut(1)=octave_value(Fs);
    argOut(2)=octave_value(bitRate);
    argOut(3)=octave_value("Temp.wav");

    feval("wavwrite",argOut,0); // Escribir el archivo temporar por medio de la funcion wavwrite de Octave
    tempFlag=true; // Bandera para indicar que se ha escrito un archivo temporal

    player=new QProcess(); // Reserva memoria dinamica para el objeto que llama al proceso

    // Conectar la senal de finalizacion del proceso con el slot que termina la reproduccion
    connect(player,SIGNAL(finished(int)),this,SLOT(playEnded()));

    // Iniciar el proceso paplay que reproduce la senal en el archivo temporal
    player->start(QString("paplay Temp.wav"));

    if (!player->waitForStarted()) {// Si no se pudo iniciar el proceso
        // playFailed();
        return;
    }

    playFlag=true; // Bandera que indica que se esta reproduciendo una senal
}

//*********************************************************************************************************************

/*
 * Slot que se ejecuta cuando termina la reproduccion, elimina los archivos temporales
 * y emite la senal que indica que la reproduccion termino
 */
void Procesamiento::playEnded()
{
    playFlag=false;
    if (tempFlag) // Si se escribio un archivo temporal
    {
        QProcess borrar; // Crear un objeto para llamar al proceso de borrar
        borrar.start(QString("rm Temp.wav")); // Iniciar el proceso de borrar
        borrar.waitForFinished(2000); // Esperar a que este termine para evitar ser eliminado antes de terminar
        tempFlag=false; // Indicar que ya no hay archivo temporal
    }
    emit finished(); // Emitir la senal que indica que la reproduccion termino
}
//*********************************************************************************************************************
/*
 * Slot que detiene la reproduccion si el usuario hace click en el boton de detener
 */
void Procesamiento::stop()
{
    if (playFlag){ // Si se esta reproduciendo la senal
        player->close(); // Indicar al objeto que lleva el proceso de reproduccion que lo cierre
        playFlag=false; // Indicar que ya no se esta reproduciendo
    }
}
//*********************************************************************************************************************

/*
 * Limpiar la senal
 */
void Procesamiento::cleanSignal(int cleanMod, int thrMod, char type)
{
    // Calcular muestra inicial y final del fragmento marcado como ruido
    long inicial = signal.rows()*iRatio;
    long final = signal.rows()*fRatio;

    octave_value_list argNS, cleanInfo; // Declarar argumentos para la eliminacion de ruido

    // Llevar los argumentos: senal, ruido (instante de la senal), Fs, bitRate, largo ventana (ms), tipo de SS, cantidad de ruido a eliminar y umbral de deteccion
    argNS(0)=octave_value(signal);
    argNS(1)=octave_value(signal.extract(octave_idx_type(inicial), octave_idx_type(0),octave_idx_type(final),octave_idx_type(0)));
    argNS(2)=octave_value(Fs);
    argNS(3)=octave_value(bitRate);
    argNS(4)=octave_value(20);

    switch (type) { // Determinar el tipo de SS a aplicar de acuerdo a la seleccion del usuario
    case 1:
        argNS(5)=octave_value("Boll");
        break;
    case 2:
        argNS(5)=octave_value("Beroutti");
        break;
    case 3:
        argNS(5)=octave_value("Kamath");
        break;
    case 4:
        argNS(5)=octave_value("CG");
        break;
    case 5:
        argNS(5)=octave_value("EMNS");
        break;
    };
    argNS(6)=octave_value(cleanMod);
    argNS(7)=octave_value(thrMod);

    // Llamar la funcion noiseSupression por medio de Octave
    cleanInfo = feval("noiseSupression", argNS,1); // Realizar SS

    clean=cleanInfo(0).matrix_value(); // Almacenar la informacion de la senal limpia en memoria

    emit finished(); // Indicar que se termino el proceso
}
//*********************************************************************************************************************
/*
 * Devolver un vector con la informacion de la senal original
 */
QVector<double> Procesamiento::getSignal()
{
    unsigned long sigSize = signal.rows(); // Obtener el tamano (numero de muestras) de la senal original
    QVector<double> y(sigSize); // Declarar el vector a devolver
    unsigned long i; // Declarar el contador
    for (i=0; i<sigSize; i++)
    {
        y[i]=signal(i); // Llenar el vector a devolver con la informacion de la senal original
    }

    return y;
}
//*********************************************************************************************************************
/*
 * Devolver un vector con la informacion de la senal limpia
 */
QVector<double> Procesamiento::getClean()
{
    unsigned long sigSize = clean.rows(); // Obtener el tamano (numero de muestras) de la senal limpia
    QVector<double> y(sigSize); // Declarar el vector a devolver
    unsigned long i; // Declarar el contador
    for (i=0; i<sigSize; i++)
    {
        y[i]=clean(i); // Llenar el vector a devolver con la informacion de la senal limpia
    }

    return y;
}
//*********************************************************************************************************************
/*
 * Devolver el tamano de la senal

unsigned long Procesamiento:: getsignalsize(){
    return signal.rows();
}

*/

long Procesamiento::getFs()
{
    return Fs(0);
}

//*********************************************************************************************************************
/*
 * Indicar la fraccion de la senal donde esta el inicio y el final del segmento escogido por el usuario
 */
void Procesamiento::setSegment(double n_iRatio, double n_fRatio)
{
    iRatio=n_iRatio;
    fRatio=n_fRatio;
}
//*********************************************************************************************************************

/*
 * Guardar a un archivo la senal limpia completa
 */
void Procesamiento::saveClean(QString Name){

    octave_value_list argSave; // Declarar la lista de argumentos para guardar

    if(Name.length()>=1){ // Dar el nombre apropiado a la senal a guardar
        Name=Name+".wav";
    }
    else{
        Name="./"+signalName + "_clean.wav";
    }

    // Llenar la lista de argumentos con la informacion de la senal limpia y el nombre del archivo
    argSave(0)=octave_value(clean);
    argSave(1)=octave_value(Fs);
    argSave(2)=octave_value(bitRate);
    argSave(3)=octave_value(Name.toAscii().data());

    feval("wavwrite",argSave,0); // Escribir el archivo utilizando la funcion wavwrite de Octave


}
//*********************************************************************************************************************
/*
 * Guardar a un archivo un fragmento, indicado por el usuario, de la senal limpia
 */
void Procesamiento::saveSegment(double n_iRatio, double n_fRatio, QString Name){

    // Calcular muestra inicial y final del fragmento marcado como ruido
    long inicial = signal.rows()*n_iRatio;
    long final = signal.rows()*n_fRatio;

    octave_value_list argSave;//argumentos para guardar

    if(Name.length()>=1){ // Dar el nombre apropiado a la senal a guardar
        Name=Name+".wav";
    }
    else{
        Name="./"+signalName + "_clean.wav";
    }

    // Llenar la lista de argumentos con la informacion de la senal limpia y el nombre del archivo
    argSave(0)=octave_value(clean.extract(octave_idx_type(inicial), octave_idx_type(0),octave_idx_type(final),octave_idx_type(0)));
    argSave(1)=octave_value(Fs);
    argSave(2)=octave_value(bitRate);
    argSave(3)=octave_value(Name.toAscii().data());

    feval("wavwrite",argSave,0); // Escribir el archivo utilizando la funcion wavwrite de Octave

}

