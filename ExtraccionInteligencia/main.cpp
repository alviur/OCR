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

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/toplev.h>
//#include <octave/builtin-defun-decls.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // crear la aplicacion de Qt
    MainWindow w; // Crear un objeto MainWidnow
    w.show(); // mostrar el objeto

    // Argumentos para octave
    argv[0] = "GUI_NS";
    argv[1] = "-q"; // Iniciar en modo silencioso (no muestra informacion de la version o la licencia

    argc = 2; // Numero de argumentos
    setlocale(LC_ALL, "en_US.UTF-8"); // Indicar a octave que se trabajara en English, o si no, no funciona
    octave_main (argc, argv, true); // Llamar al main de octave
    feval("inicializar");


    return a.exec(); // Ejecutar la aplicacion Qt
}
