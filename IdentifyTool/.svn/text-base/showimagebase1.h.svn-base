#ifndef SHOWIMAGEBASE1_H
#define SHOWIMAGEBASE1_H

#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QPainter>
#include <QPen>
#include <QDesktopWidget>
#include <QRect>
#include <gdal.h>
#include <gdal_priv.h>
#include <math.h>
#include "ui_showimagebase1.h"
#include "identifyimage.h"
#include "transvoidtoint.h"


#define nShowImageWidth 700

class ShowImageBase1 : public QGraphicsView
{
  Q_OBJECT

    public:
  ShowImageBase1(QWidget *parent = 0);
  ShowImageBase1(QWidget *,GDALDataset*);
  ~ShowImageBase1();

 private:
  Ui::ShowImageBase1 ui;

 public:
  QImage *pImageBase1;
  QPoint nPointMouseClick,nPointMouseRelease,nPointDoubleClick,nPointLeftClickDown,nPointLeftClickRelease,nPointMouseMove1,nPointMouseMove2,nPointStartRect; //mouse position;
  QGraphicsRectItem *nRectItem;
  QGraphicsScene *scene;
  IdentifyImage *pImagebaseUI2;

  GDALDataset* pDataset;
  GDALRasterBand *pRasterBand,*pRasterBandRed,*pRasterBandGreen,*pRasterBandBlue;
  GDALDataType nBandType;

  int nWidth,nHeight;
  int    nRectWidth;
  bool nMousePressed,nMouseRealsed;
  bool bImageColor;//flags for the gray and color image;
  double adfCMinMax[2],adfCMinMaxRed[2],adfCMinMaxGreen[2],adfCMinMaxBlue[2];
  double dfscale,dfRedScale,dfGreenScale,dfBlueScale;
  double nScaleFactorWidth,nScaleFactorHeight;//the rect width and the shown image width;
  int nRGBofBase[3];

 public:
  bool ShowOverviewGray();//show gray image;
  bool ShowOverviewColor(int *);//show color image;
  bool CreatQimage(QImage*);
  bool CreatQimageColor(QImage*);
  bool CalRectWidth();
  QPoint TransOvToSrcPos(QPoint);
 
  public slots:
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *event);
  void GetPosition(QPoint);
  void closeEvent(QCloseEvent *);

 signals:
  void ReportPosition(QPoint);
  void ReprotCloseWindow();

};
#endif // SHOWIMAGEBASE1
