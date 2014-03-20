#include <QtGui/QApplication>
#include "showimagebase1.h"
#include "mymainwindow.h"
#include <gdal.h>
#include <gdal_priv.h>

#define nShowImageWidth 700
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GDALAllRegister();
    MyMainWindow w;
    w.show();
    return a.exec();
}
