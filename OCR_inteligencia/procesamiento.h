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

#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <QObject>
#include <QVector>
#include <QString>
#include <QProcess>


/*
 * Esta clase se encarga del procesamiento de la senal es decir:
 * Cargar las senales desde el disco duro o medio de almacenamiento
 * Reproducir las senales o fragmentos de ellas
 * Limpiar las senales
 * Guardar las senales limpias o fragmentos de ellas
 **/

class Procesamiento : public QObject
{
    Q_OBJECT

public:
    Procesamiento(QObject *parent = 0);
    Procesamiento(Procesamiento* toCopy);
    ~Procesamiento();

public slots:

    // Abrir la senal
    void openSignal(char* fileName);
    // Reproducir
    void playSignal();    
    void playClean();
    void playSegment();
    void playCleanSegment();
    void playEnded();
    void stop();
    // Limpiar
    void cleanSignal(int cleanMod,int thrMod,char type);

    // Obtener la informacion de las senales
    QVector<double> getSignal();
    QVector<double> getClean();
    //unsigned long getsignalsize();
    long getFs();

    // Ingresar la informacion del segmento
    void setSegment(double n_iRatio, double n_fRatio);
    // Guardar
    void saveClean(QString Name);    
    void saveSegment(double n_iRatio, double n_fRatio, QString Name);


signals:
    void finished();
    void error(QString err);

private:
    Matrix signal; // Matriz, tipo de octave, en donde se guarda la informacion de las muestras de la senal original
    Matrix Fs; // Matriz, tipo de octave, en donde se guarda la informacion de la frecuencia de muestreo
    Matrix bitRate; // Matriz, tipo de octave, en donde se guarda la informacion de la tasa de bits
    Matrix clean; // Matriz, tipo de octave, en donde se guarda la informacion de las muestras de la senal limpia
    double iRatio, fRatio; // Indican la fraccion inicial y final del segmento de la senal seleccionado por el usuario
    QString signalName; // Ruta y nombre de archivo de la senal original
    bool playFlag; // Bandera de reproduccion
    bool tempFlag; // Bandera de archivo temporal
    QProcess* player; // Objeto que maneja el proceso de reproduccion

};

#endif // PROCESAMIENTO_H
