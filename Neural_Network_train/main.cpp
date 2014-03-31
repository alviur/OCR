#include <QApplication>
#include "train.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Train w;
    w.show();
    
    return a.exec();
}
