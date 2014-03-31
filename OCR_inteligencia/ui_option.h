/********************************************************************************
** Form generated from reading UI file 'option.ui'
**
** Created: Sat Feb 1 22:38:35 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTION_H
#define UI_OPTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_option
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *type1Button;
    QRadioButton *type2Button;
    QRadioButton *type3Button;
    QRadioButton *type4Button;
    QRadioButton *type5Button;
    QSlider *cleanSlider;
    QSlider *thrSlider;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *cleanLcd;
    QLCDNumber *thrLcd;

    void setupUi(QDialog *option)
    {
        if (option->objectName().isEmpty())
            option->setObjectName(QString::fromUtf8("option"));
        option->resize(380, 274);
        buttonBox = new QDialogButtonBox(option);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 230, 341, 32));
        buttonBox->setCursor(QCursor(Qt::PointingHandCursor));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        type1Button = new QRadioButton(option);
        type1Button->setObjectName(QString::fromUtf8("type1Button"));
        type1Button->setGeometry(QRect(20, 40, 111, 17));
        type1Button->setCursor(QCursor(Qt::PointingHandCursor));
        type1Button->setMouseTracking(true);
        type1Button->setChecked(false);
        type1Button->setAutoRepeat(false);
        type1Button->setAutoExclusive(true);
        type2Button = new QRadioButton(option);
        type2Button->setObjectName(QString::fromUtf8("type2Button"));
        type2Button->setGeometry(QRect(20, 70, 111, 17));
        type2Button->setCursor(QCursor(Qt::PointingHandCursor));
        type2Button->setMouseTracking(true);
        type2Button->setAutoExclusive(true);
        type3Button = new QRadioButton(option);
        type3Button->setObjectName(QString::fromUtf8("type3Button"));
        type3Button->setGeometry(QRect(20, 100, 121, 17));
        type3Button->setCursor(QCursor(Qt::PointingHandCursor));
        type3Button->setMouseTracking(true);
        type4Button = new QRadioButton(option);
        type4Button->setObjectName(QString::fromUtf8("type4Button"));
        type4Button->setGeometry(QRect(20, 130, 101, 17));
        type4Button->setCursor(QCursor(Qt::PointingHandCursor));
        type4Button->setMouseTracking(true);
        type5Button = new QRadioButton(option);
        type5Button->setObjectName(QString::fromUtf8("type5Button"));
        type5Button->setGeometry(QRect(20, 160, 111, 17));
        type5Button->setCursor(QCursor(Qt::PointingHandCursor));
        type5Button->setMouseTracking(true);
        cleanSlider = new QSlider(option);
        cleanSlider->setObjectName(QString::fromUtf8("cleanSlider"));
        cleanSlider->setGeometry(QRect(180, 60, 160, 24));
        cleanSlider->setCursor(QCursor(Qt::PointingHandCursor));
        cleanSlider->setMinimum(1);
        cleanSlider->setMaximum(10);
        cleanSlider->setValue(5);
        cleanSlider->setOrientation(Qt::Horizontal);
        thrSlider = new QSlider(option);
        thrSlider->setObjectName(QString::fromUtf8("thrSlider"));
        thrSlider->setGeometry(QRect(180, 130, 160, 24));
        thrSlider->setCursor(QCursor(Qt::PointingHandCursor));
        thrSlider->setMinimum(1);
        thrSlider->setMaximum(5);
        thrSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(option);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 110, 121, 17));
        label_2 = new QLabel(option);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 40, 191, 20));
        cleanLcd = new QLCDNumber(option);
        cleanLcd->setObjectName(QString::fromUtf8("cleanLcd"));
        cleanLcd->setGeometry(QRect(200, 80, 64, 23));
        cleanLcd->setProperty("intValue", QVariant(5));
        thrLcd = new QLCDNumber(option);
        thrLcd->setObjectName(QString::fromUtf8("thrLcd"));
        thrLcd->setGeometry(QRect(200, 160, 64, 23));
        thrLcd->setProperty("intValue", QVariant(1));

        retranslateUi(option);
        QObject::connect(buttonBox, SIGNAL(accepted()), option, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), option, SLOT(reject()));

        QMetaObject::connectSlotsByName(option);
    } // setupUi

    void retranslateUi(QDialog *option)
    {
        option->setWindowTitle(QApplication::translate("option", "Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        type1Button->setToolTip(QApplication::translate("option", "Con este metodo podra realizar limpieza de cualquier tipo de se\303\261al. Baja efectividad en la limpieza. Menor tiempo de procesamiento.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        type1Button->setText(QApplication::translate("option", "method 1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        type2Button->setToolTip(QApplication::translate("option", "Con este metodo podra realizar limpieza de cualquier tipo de se\303\261al. Limpieza intermedia. Tiempo de procesamiento bajo.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        type2Button->setText(QApplication::translate("option", "method 2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        type3Button->setToolTip(QApplication::translate("option", "Con este metodo podra realizar limpieza de se\303\261ales de voz. Limpieza buena. Tiempo de procesamiento alto.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        type3Button->setText(QApplication::translate("option", "method 3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        type4Button->setToolTip(QApplication::translate("option", "Con este metodo podra realizar mejor limpieza de se\303\261ales de voz. Limpieza buena. Mayor tiempo de procesamiento requerido.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        type4Button->setText(QApplication::translate("option", "method 4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        type5Button->setToolTip(QApplication::translate("option", "Con este metodo podra realizar limpieza de cualquier tipo de se\303\261al. Alta efectividad de limpieza. Tiempo de procesamiento alto.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        type5Button->setText(QApplication::translate("option", "method 5", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("option", "noise threshold", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("option", "amount of noise to remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class option: public Ui_option {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTION_H
