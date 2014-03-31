#-------------------------------------------------
#
# Project created by QtCreator 2012-12-18T14:16:43
#
#-------------------------------------------------

# Programa para limpiar señales de voz

QT       += core gui

TARGET = interfaz1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linearregretion.cpp \
    integralproy.cpp \
    hog.cpp \
    fourier.cpp \
    simage.cpp \
    Ssobel.cpp

HEADERS  += mainwindow.h \
    linearregretion.h \
    integralproy.h \
    hog.hpp \
    fourier.h \
    simage.h \
    Ssobel.hpp

FORMS    += mainwindow.ui


#INCLUDEPATH += /usr/include/octave-3.2.4/
#LIBS += -L"/usr/lib/octave-3.2.4/" -loctinterp -loctave

LIBS += -llapack -lblas -larmadillo

unix{
    CONFIG += link_pkgconfig
    PKGCONFIG +=opencv
}
win32{
    INCLUDEPATH += C:\opencv246bin\install\include \
                   C:\opencv246bin\install\include\opencv \
                   C:\opencv246bin\install\include\opencv2

    LIBS += -LC:\\opencv246bin\\install\\lib \
            -lopencv_core246.dll \
            -lopencv_highgui246.dll \
            -lopencv_imgproc246.dll \
            -lopencv_features2d246.dll \
            -lopencv_calib3d246.dll \
            -lopencv_video246.dll \
            -lopencv_videostab246.dll

}

INCLUDEPATH += /usr/include/octave-3.6.2/
LIBS += -L"/usr/lib/x86_64-linux-gnu/" -loctinterp -loctave

INCLUDEPATH += /usr/include/octave-3.6.1/
LIBS += -L"/usr/lib/i386-linux-gnu/" -loctinterp -loctave


OTHER_FILES += \
    ../Graficos/stop.png \
    ../Graficos/playsegment.png \
    ../Graficos/play.png
