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

#include "option.h"
#include "ui_option.h"

//*********************************************************************************************
/*
 * Constructor por defecto
 */
option::option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::option)
{
    ui->setupUi(this); // Inicializar la interfaz grafica

    // Conectar las senales de los sliders con las senales de los LCDNumber que muestran sus valores
    connect(ui->cleanSlider,SIGNAL(valueChanged(int)),ui->cleanLcd, SLOT(display(int)));
    connect(ui->thrSlider,SIGNAL(valueChanged(int)),ui->thrLcd, SLOT(display(int)));
}

//*******************************************************************************************
/*
 * Destructor
 */
option::~option()
{
    delete ui; // Liberar memoria dinamica
}

//*****************************************************************************************************
/*
 * Slots al dar aceptar o cancelar en el dialogo, no hacen nada
 */

void option::on_buttonBox_accepted()
{

}

void option::on_buttonBox_rejected()
{
    //cerrar
}

//******************************************************************************************************
/*
 * Slot para obtener el tipo de metodo de SS a utilizar seleccionado
 */

char option::getType()
{
    return type;
}

//******************************************************************************************************
/*
 * Funcion para inicializar el tipo de metodo de SS seleccionado
 */

void option::setType(char typeNow)
{
    switch(typeNow){
    case 1:
        ui->type1Button->click();
        break;
    case 2:
        ui->type2Button->click();
        break;
    case 3:
        ui->type3Button->click();
        break;
    case 4:
        ui->type4Button->click();
        break;
    case 5:
        ui->type5Button->click();
        break;
    };
}

//***********************************************************************************************
/*
 * Devolver el valor del parametro de umbral
 */
int option::getThrMod()
{
    return ui->thrSlider->value();
}

//**********************************************************************************************
/*
 * Funcion para inicializar el valor del parametro de umbral
 */

void option::setThrMod(int thrMod)
{
    ui->thrSlider->setValue(thrMod);
}

//****************************************************************************************************
/*
 * Devolver el valor del parametro de limpieza
 */
int option::getCleanMod()
{
    return ui->cleanSlider->value();
}

//**********************************************************************************************
/*
 * Funcion para inicializar el valor del parametro de de limpieza
 */

void option::setCleanMod(int cleanMod)
{
    ui->cleanSlider->setValue(cleanMod);
}

//*******************************************************************************************************
/*
 * Slots que se llaman al hacer click en los botones para seleccionar el tipo de SS
 * Ajustan adecuadamente el valor del tipo y activan o desactivan el slider del parametro de limpieza
 */

void option::on_type1Button_clicked()
{
    type=1;
    ui->cleanSlider->setDisabled(1);
    //m.setText("Con este metodo podra realizar limpieza de cualquier tipo de señal. Baja efectividad en la limpieza. Menor tiempo de procesamiento.");
    //m.exec();
}

void option::on_type2Button_clicked()
{
    type=2;
    ui->cleanSlider->setEnabled(1);
    //m.setText("Con este metodo podra realizar limpieza de cualquier tipo de señal. Limpieza intermedia. Tiempo de procesamiento bajo.");
    //m.exec();
}

void option::on_type3Button_clicked()
{
    type=3;
    ui->cleanSlider->setEnabled(1);
    //m.setText("Con este metodo podra realizar limpieza de señales de voz. Limpieza buena. Tiempo de procesamiento alto.");
    //m.exec();
}

void option::on_type4Button_clicked()
{
    //sleep(1);
    type=4;
    ui->cleanSlider->setEnabled(1);
    //m.setText("Con este metodo podra realizar mejor limpieza de señales de voz. Limpieza buena. Mayor tiempo de procesamiento requerido.");
    //m.exec();
}

void option::on_type5Button_clicked()
{
    type=5;
    ui->cleanSlider->setDisabled(1);
    //m.setText("Con este metodo podra realizar limpieza de cualquier tipo de señal. Alta efectividad de limpieza. Tiempo de procesamiento alto.");
    //m.exec();
}
