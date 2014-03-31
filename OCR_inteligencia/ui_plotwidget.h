/********************************************************************************
** Form generated from reading UI file 'plotwidget.ui'
**
** Created: Sat Feb 1 22:38:35 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWIDGET_H
#define UI_PLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_plotWidget
{
public:
    QCustomPlot *graphicsig;
    QPushButton *playsignal;
    QPushButton *playsegment;
    QPushButton *stop;

    void setupUi(QWidget *plotWidget)
    {
        if (plotWidget->objectName().isEmpty())
            plotWidget->setObjectName(QString::fromUtf8("plotWidget"));
        plotWidget->resize(644, 150);
        plotWidget->setMouseTracking(true);
        graphicsig = new QCustomPlot(plotWidget);
        graphicsig->setObjectName(QString::fromUtf8("graphicsig"));
        graphicsig->setGeometry(QRect(0, 0, 600, 150));
        graphicsig->setMouseTracking(true);
        playsignal = new QPushButton(plotWidget);
        playsignal->setObjectName(QString::fromUtf8("playsignal"));
        playsignal->setGeometry(QRect(600, 0, 41, 41));
        playsignal->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Graficos/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playsignal->setIcon(icon);
        playsignal->setIconSize(QSize(30, 30));
        playsegment = new QPushButton(plotWidget);
        playsegment->setObjectName(QString::fromUtf8("playsegment"));
        playsegment->setGeometry(QRect(600, 40, 41, 41));
        playsegment->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Graficos/playsegment.png"), QSize(), QIcon::Normal, QIcon::Off);
        playsegment->setIcon(icon1);
        playsegment->setIconSize(QSize(30, 30));
        stop = new QPushButton(plotWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(600, 80, 41, 41));
        stop->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../Graficos/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stop->setIcon(icon2);
        stop->setIconSize(QSize(30, 30));

        retranslateUi(plotWidget);

        QMetaObject::connectSlotsByName(plotWidget);
    } // setupUi

    void retranslateUi(QWidget *plotWidget)
    {
        plotWidget->setWindowTitle(QApplication::translate("plotWidget", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        playsignal->setToolTip(QApplication::translate("plotWidget", "Reproducir se\303\261al completa", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        playsignal->setText(QString());
#ifndef QT_NO_TOOLTIP
        playsegment->setToolTip(QApplication::translate("plotWidget", "Reproducir segmento", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        playsegment->setText(QString());
#ifndef QT_NO_TOOLTIP
        stop->setToolTip(QApplication::translate("plotWidget", "Detener reproducci\303\263n", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class plotWidget: public Ui_plotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWIDGET_H
