#ifndef TRAIN_H
#define TRAIN_H

#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include<anntrain.h>
#include<integralproy.h>
#include<QProcess>
#include <string>
#include"hog.hpp"
#include"Ssobel.hpp"
#include"scontour.h"
#include"integralproy.h"
#include"simage.h"

namespace Ui {
class Train;
}

class Train : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Train(QWidget *parent = 0);
    ~Train();

    AnnTrain net;
    cv::Mat TrainData;
    cv::Mat TrainDataOutput;

    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Train *ui;
};

#endif // TRAIN_H
