#ifndef SHOWIMAGEBASE2_H
#define SHOWIMAGEBASE2_H

#include <QImage>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QGraphicsLineItem>
#include <QDesktopWidget>
#include <QRect>
#include <gdal.h>
#include <gdal_priv.h>
#include <math.h>
#include <stdint.h>
#include "ui_showimagebase2.h"
#include "transvoidtoint.h"

#define nShowImageWidth 700

class ShowImageBase2 : public QGraphicsView
{
	Q_OBJECT

public:
	ShowImageBase2(QWidget *parent = 0);
    ShowImageBase2(QWidget *parent,GDALDataset*);//Add three parameters to specific dataset,overview and sizeof overview rubber;
	~ShowImageBase2();

private:
    Ui::ShowImageBase2 ShowImage2ui;

protected:
	GDALDataset* pDataset;
	GDALRasterBand *pRasterBand,*pRasterBandRed,*pRasterBandGreen,*pRasterBandBlue;
    GDALDataType nBandType;

	QPoint nPointStartShown,nPointEndShown,nPointBase;
	QGraphicsScene *scene;
	QGraphicsView *view;

	double adfCMinMax[2],adfCMinMaxRed[2],adfCMinMaxGreen[2],adfCMinMaxBlue[2];
	double dfscale,dfRedScale,dfGreenScale,dfBlueScale;
	int nRGBofBase[3];
	bool showGrayImage;

public:
	void CalBoundary();
    bool CreatQimage(QImage*);
	bool CreatQimageColor(QImage*,void*,void*,void*);
	bool MoveImage(QPoint);
	bool MoveImageColor(QPoint);
	bool InitPara();// Create enough labels to contain qimages.
	void wheelEvent(QWheelEvent *event);
	void GetRasterband(int *);

signals:
	void ReportPosition(QPoint);
};

#endif // SHOWIMAGEBASE2_H
