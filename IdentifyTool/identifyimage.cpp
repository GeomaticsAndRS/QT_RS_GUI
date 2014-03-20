#include "identifyimage.h"
#include "ui_identifyimage.h"

IdentifyImage::IdentifyImage(QWidget *parent) :
    ShowImageBase2(parent),
    ui(new Ui::IdentifyImage)
{
    ui->setupUi(this);
}

IdentifyImage::IdentifyImage(QWidget *parent,GDALDataset* p_Dataset):
    ShowImageBase2(parent,p_Dataset),
    ui(new Ui::IdentifyImage)
{
    ui->setupUi(this);
    setWindowTitle("IdentifyWindow");
    resize(nShowImageWidth,nShowImageWidth);
}


IdentifyImage::~IdentifyImage()
{
    delete ui;
}

void IdentifyImage::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF n_Point1;
    n_Point1=mapToScene(event->x(),event->y());
    QPoint n_PointMouseDbClick;
    n_PointMouseDbClick.rx()=n_Point1.x()+nPointStartShown.x();
    n_PointMouseDbClick.ry()=n_Point1.y()+nPointStartShown.y();
    GetPositionData(n_PointMouseDbClick);
}

void IdentifyImage::GetPositionData(QPoint n_PointPos)
{
    GDALRasterBand *p_RasterBand;
    int count;
    count=pDataset->GetRasterCount();
    double n_PixelValue[4];
    for(int i=0;i<count;i++)
    {
         p_RasterBand=pDataset->GetRasterBand(i+1);
         void *p_BandData=malloc(sizeof(nBandType));
         p_RasterBand->RasterIO(GF_Read,n_PointPos.x(),n_PointPos.y(),1,1,p_BandData,1,1,nBandType,0,0);
         TransVoidToIntOne Trans(p_RasterBand,p_BandData,nBandType);
         n_PixelValue[i%4]=Trans.GetValue(0);
    }
    QString n_String=QString("Value: %1 %2 %3 %4").arg(n_PixelValue[0]).arg(n_PixelValue[1]).arg(n_PixelValue[0]).arg(n_PixelValue[0]);
    QClipboard *p_ClipBoard=QApplication::clipboard();
    p_ClipBoard->clear();
    p_ClipBoard->setText(n_String);
}
