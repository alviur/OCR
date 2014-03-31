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

#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class option;
}

/*
 * Esta clase es la ventana de opciones del programa
 * se muestra al hacer click en el boton de opciones de la ventana principal.
 * Los slots privados se llaman al hacer click en los diferentes botones de la ventana.
 * Los slots publicos sirven para devolver los valores de las diferentes opciones
 * o para inicializar los valores antes de mostrar la ventana.
 **/

class option : public QDialog
{
    Q_OBJECT
    
public:
    explicit option(QWidget *parent = 0);
    ~option();

    char getType();
    void setType(char typeNow);
    int getThrMod();
    void setThrMod(int thrMod);
    int getCleanMod();
    void setCleanMod(int cleanMod);

    
private slots:

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_type1Button_clicked();
    void on_type2Button_clicked();
    void on_type3Button_clicked();
    void on_type4Button_clicked();
    void on_type5Button_clicked();

private:
    Ui::option *ui; // Interfaz grafica
    char type; // Tipo de SS
    QMessageBox m;

};

#endif // OPTION_H
