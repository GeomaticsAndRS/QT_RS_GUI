#include "showimagebase1.h"

ShowImageBase1::ShowImageBase1(QWidget *parent)
  : QGraphicsView(parent)
{
  ui.setupUi(this);
}

ShowImageBase1::~ShowImageBase1()
{
}

ShowImageBase1::ShowImageBase1(QWidget *parent,GDALDataset* p)
  : QGraphicsView(parent)
{
  ui.setupUi(this);
  pDataset=p;

  scene=new QGraphicsScene;
  setWindowTitle("ImageBase1");
  setScene(scene);
  resize(250,150);
  show();

  QDesktopWidget desktopwidg;
  const QRect screen=desktopwidg.screenGeometry(-1);
  move(screen.x()+10,screen.y()+530);

  bImageColor=false;

  pImagebaseUI2=new IdentifyImage(0,pDataset);
  connect(pImagebaseUI2,SIGNAL(ReportPosition(QPoint)),this,SLOT(GetPosition(QPoint)));
  connect(this,SIGNAL(ReprotCloseWindow()),pImagebaseUI2,SLOT(close()));
}

bool ShowImageBase1::ShowOverviewGray()
{
  //show the top view of pyramid,we have build the overview for the image before;
  GDALRasterBand  *poBand1,*poBand2;
  poBand1=pDataset->GetRasterBand(1);

  int n=poBand1->GetOverviewCount();
  poBand2=poBand1->GetOverview(n-1);//n start from 0;

  nBandType=poBand2->GetRasterDataType();
  nWidth=poBand2->GetXSize();
  nHeight=poBand2->GetYSize();

  //CheckScalePix(poBand2,&dfscale,adfCMinMax);
  pRasterBand=poBand2;
  pImageBase1=new QImage(nWidth,nHeight,QImage::Format_RGB888);
  CreatQimage(pImageBase1);
	
  QGraphicsItem *items=scene->addPixmap(QPixmap::fromImage(*pImageBase1));
  items->setPos(0,0);
  CalRectWidth();

  pImagebaseUI2->MoveImage(QPoint(0,0));
  return true;
}

bool ShowImageBase1::ShowOverviewColor(int *nRGBofBasetemp)
{
  nRGBofBase[0]=nRGBofBasetemp[0];
  nRGBofBase[1]=nRGBofBasetemp[1];
  nRGBofBase[2]=nRGBofBasetemp[2];

  //show the top view of pyramid
  GDALRasterBand  *poBand1,*poBand2,*poBand3;
  poBand1=pDataset->GetRasterBand(nRGBofBase[0]);
  poBand2=pDataset->GetRasterBand(nRGBofBase[1]);
  poBand3=pDataset->GetRasterBand(nRGBofBase[2]);

  int n=poBand1->GetOverviewCount();
  pRasterBandRed=poBand1->GetOverview(n-1);//start from 0;
  pRasterBandGreen=poBand2->GetOverview(n-1);
  pRasterBandBlue=poBand3->GetOverview(n-1);

  nWidth=pRasterBandRed->GetXSize();
  nHeight=pRasterBandRed->GetYSize();
  nBandType=pRasterBandRed->GetRasterDataType();

  pImageBase1=new QImage(nWidth,nHeight,QImage::Format_RGB888);
  CreatQimageColor(pImageBase1);

  QGraphicsItem *items=scene->addPixmap(QPixmap::fromImage(*pImageBase1));
  items->setPos(0,0);
  CalRectWidth();

  pImagebaseUI2->GetRasterband(nRGBofBase);
  pImagebaseUI2->MoveImage(QPoint(0,0));
  return true;
}

void ShowImageBase1::mousePressEvent(QMouseEvent *e)
{
  QPointF p;
  p=mapToScene(e->x(),e->y());
  nPointMouseClick.rx()=p.x();
  nPointMouseClick.ry()=p.y();

  nPointMouseMove1=nPointMouseClick;
  nPointMouseMove2=nPointMouseClick;
}

void ShowImageBase1::mouseMoveEvent(QMouseEvent *e)
{
  QPointF n_PointMouse;
  int n_dx,n_dy;
  n_PointMouse=mapToScene(e->x(),e->y());
  nPointMouseMove2.rx()=n_PointMouse.x();
  nPointMouseMove2.ry()=n_PointMouse.y();

  n_dx=nPointMouseMove2.x()-nPointMouseMove1.x();
  n_dy=nPointMouseMove2.y()-nPointMouseMove1.y();

  //confirm the rectitem is within the range of overview image
  if (nPointStartRect.x()+n_dx<0)
    {
      nPointStartRect.rx()=0;
      n_dx=0;
    }
  if (nPointStartRect.y()+n_dy<0)
    {
      nPointStartRect.ry()=0;
      n_dy=0;
    }
  if (nPointStartRect.x()+n_dx>nWidth-nRectWidth)
    {
      nPointStartRect.rx()=nWidth-nRectWidth;
      n_dx=0;
		
    }
  if (nPointStartRect.y()+n_dy>nHeight-nRectWidth)
    {
      nPointStartRect.ry()=nHeight-nRectWidth;
      n_dy=0;
    }
  nPointStartRect.rx()=nPointStartRect.x()+n_dx;
  nPointStartRect.ry()=nPointStartRect.y()+n_dy;


  nRectItem->setPos(nPointStartRect.x(),nPointStartRect.y());
  nPointMouseMove1=nPointMouseMove2;
}

void ShowImageBase1::mouseReleaseEvent(QMouseEvent *e)
{
  //show corresponding image
  if (!bImageColor)
    {
      //show gray image in imagebaseUI2;
      pImagebaseUI2->MoveImage(TransOvToSrcPos(nPointStartRect));
    }
}

bool ShowImageBase1::CreatQimage(QImage* pimage)
{
  QRgb nPixelValue;
  int n_val1;

  void *p_Banddata1=malloc(nWidth*nHeight*sizeof(nBandType));
  pRasterBand->RasterIO(GF_Read,0,0,nWidth,nHeight,p_Banddata1,nWidth,nHeight,nBandType,0,0);
  TransVoidToInt Trans(pRasterBand,p_Banddata1,nBandType);

  for (int i=0;i<nHeight;i++)
    for(int j=0;j<nWidth;j++)
      {
	//translate the void type to a int type data 
    n_val1=Trans.GetValue(i*nWidth+j);
    nPixelValue=qRgb(n_val1,n_val1,n_val1);
    pimage->setPixel(j,i,nPixelValue);
      }
  delete[] p_Banddata1;
  return true;
}

bool ShowImageBase1::CreatQimageColor(QImage* pimage)
{
  QRgb nPixelValue;
  int n_Value1,n_Value2,n_Value3;
  //translate the void type to a int type data

  void *p_Banddata1=malloc(nWidth*nHeight*sizeof(nBandType));
  void *p_Banddata2=malloc(nWidth*nHeight*sizeof(nBandType));
  void *p_Banddata3=malloc(nWidth*nHeight*sizeof(nBandType));

  pRasterBandRed->RasterIO(GF_Read,0,0,nWidth,nHeight,p_Banddata1,nWidth,nHeight,nBandType,0,0);
  pRasterBandGreen->RasterIO(GF_Read,0,0,nWidth,nHeight,p_Banddata2,nWidth,nHeight,nBandType,0,0);
  pRasterBandBlue->RasterIO(GF_Read,0,0,nWidth,nHeight,p_Banddata3,nWidth,nHeight,nBandType,0,0);

  TransVoidToInt TransRed(pRasterBandRed,p_Banddata1,nBandType);
  TransVoidToInt TransGreen(pRasterBandGreen,p_Banddata2,nBandType);
  TransVoidToInt TransBlue(pRasterBandBlue,p_Banddata3,nBandType);

  for (int i=0;i<nHeight;i++) 
    for(int j=0;j<nWidth;j++)
      {	
    n_Value1=TransRed.GetValue(i*nWidth+j);
    n_Value2=TransGreen.GetValue(i*nWidth+j);
    n_Value3=TransBlue.GetValue(i*nWidth+j);
    nPixelValue=qRgb(n_Value1,n_Value2,n_Value3);
    pimage->setPixel(j,i,nPixelValue);
      }
  delete[] p_Banddata1;
  delete[] p_Banddata2;
  delete[] p_Banddata3;
  return true;
}

bool ShowImageBase1::CalRectWidth()
{
  //calculate the width of the cross
  GDALRasterBand *p1=pDataset->GetRasterBand(1);
  int n=p1->GetOverviewCount();
  GDALRasterBand *p2=p1->GetOverview(n-1);

  nScaleFactorWidth=p1->GetXSize()/p2->GetXSize();
  nScaleFactorHeight=p1->GetYSize()/p2->GetYSize();
  //the number of 400 is the probably the display size of image two.
  nRectWidth=nShowImageWidth/nScaleFactorWidth;
	
  if (nRectWidth>p2->GetXSize())
    {
      nRectWidth=p2->GetXSize();
    }
  if (nRectWidth>p2->GetYSize())
    {
      nRectWidth=p2->GetYSize();
    }
  nRectItem=scene->addRect(0,0,nRectWidth,nRectWidth,QPen(Qt::red));
  return true;
}

void ShowImageBase1::wheelEvent(QWheelEvent *event)
{
  if (event->delta()<0)
    scale(0.8,0.8);
  else
    scale(1.2,1.2);
}

QPoint ShowImageBase1::TransOvToSrcPos(QPoint n_PointOV)
{
    QPoint n_PointSrc;
    n_PointSrc.rx()=n_PointOV.x()*nScaleFactorWidth;
    n_PointSrc.ry()=n_PointOV.y()*nScaleFactorHeight;
    return n_PointSrc;
}

void ShowImageBase1::GetPosition(QPoint p)
{
  emit ReportPosition(p);
}

void ShowImageBase1::closeEvent(QCloseEvent *e)
{
  emit ReprotCloseWindow();
  e->accept();
}

