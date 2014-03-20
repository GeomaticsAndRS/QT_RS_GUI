#ifndef IDENTIFYIMAGE_H
#define IDENTIFYIMAGE_H

#include <QWidget>
#include <QPoint>
#include <QClipboard>
#include <gdal.h>
#include <gdal_priv.h>
#include "showimagebase2.h"
#include "transvoidtointone.h"

namespace Ui {
class IdentifyImage;
}

class IdentifyImage : public ShowImageBase2
{
    Q_OBJECT
    
public:
    explicit IdentifyImage(QWidget *parent = 0);
    IdentifyImage(QWidget *parent,GDALDataset*);
    ~IdentifyImage();
    
private:
    Ui::IdentifyImage *ui;

public:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void GetPositionData(QPoint);
};

#endif // IDENTIFYIMAGE_H
