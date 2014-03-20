#include "geometrycorrection.h"

GeometryCorrection::GeometryCorrection(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	InitUI();
	adjustSize();

	pBaseFileDataset=NULL;

	connect(pushButtonLoadImage,SIGNAL(clicked()),this,SLOT(slotAddImage()));
	connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem *, int )),this,SLOT(slotTreeClicked(QTreeWidgetItem *, int)));
	connect(radioButtonGray,SIGNAL(clicked()),this,SLOT(slotRadioGrayClicked()));
	connect(radioButtonRgb,SIGNAL(clicked()),this,SLOT(slotRadioColorClicked()));
	connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slotTreeDoubleClicked(QTreeWidgetItem*,int)));
	connect(pushButtonCancel,SIGNAL(clicked()),this,SLOT(close()));
}

GeometryCorrection::~GeometryCorrection()
{
}

void GeometryCorrection::slotActionOpenBaseFile()
{
	//open file dialog to choose base file
	if (pBaseFileDataset)
		return;
	mBaseFileName= QFileDialog::getOpenFileName(this, tr("Open File"),
		"/home");

	GDALAllRegister();

	pBaseFileDataset=(GDALDataset *)GDALOpen(mBaseFileName.toStdString().data(),GA_ReadOnly);

	if (pBaseFileDataset==NULL)
		return;

    if(!CheckOverView(pBaseFileDataset))
        return;

	GetBaseFileMapinfo(mBaseFileName);


}

bool GeometryCorrection::GetBaseFileMapinfo(QString filename)
{
	//to get image infomation. flag 1 is base image and 2 warp image
	treeBaseItem->setText(0,filename);
	int n=pBaseFileDataset->GetRasterCount();
	//to construct n treewidgetiterm
	QList<QTreeWidgetItem *> items;
	QTreeWidgetItem *p;
	for (int i = 0; i < n; ++i)
	{
		 p=new QTreeWidgetItem();
		//get raster band information£»
		GDALRasterBand *poBand=pBaseFileDataset->GetRasterBand(i+1);
		char *poBandDescription=new char[100];
		const char* ptemp=poBand->GetDescription();
		strcpy(poBandDescription,ptemp);
		QString poDes=QString(QLatin1String(poBandDescription));
		p->setText(0,poDes);
		if (sizeof(*ptemp)<2)
			p->setText(0,QString("layer %0").arg(i+1));
		items.append(p);
		treeBaseLayerItem.append(p);
		delete[] poBandDescription;
	}

	p=new QTreeWidgetItem();
	QString str="Map Info";
	p->setText(0,str);
	items.append(p);
	treeBaseItem->insertChildren(0,items);

	items.clear();
	//to get projection
	const char* strchr=pBaseFileDataset->GetProjectionRef();
	char* strchr1=new char[100];
	memcpy(strchr1,strchr,100);
	QTreeWidgetItem *q=new QTreeWidgetItem();
	QString poDes2=QString(QLatin1String(strchr1));
	q->setText(0,poDes2);
	items.append(q);
	treeBaseMapinfoItem=q;
	delete[] strchr1;

	double adfGeoTransform[6];
	pBaseFileDataset->GetGeoTransform( adfGeoTransform );
	strchr1=new char[100];
	sprintf(strchr1,"Pixel: %f",adfGeoTransform[1]);
	QString poDes3=QString(QLatin1String(strchr1));
	q=new QTreeWidgetItem();
	q->setText(0,poDes3);
	items.append(q);
	delete[] strchr1;

	strchr1=new char[100];	
	sprintf(strchr1,"UL X: %.2f",adfGeoTransform[0]);
	QString poDes4=QString(QLatin1String(strchr1));
	q=new QTreeWidgetItem();
	q->setText(0,poDes4);
	items.append(q);
	delete[] strchr1;

	strchr1=new char[100];
	sprintf(strchr1,"UL Y: %.2f",adfGeoTransform[3]);
	QString poDes5=QString(QLatin1String(strchr1));
	q=new QTreeWidgetItem();
	q->setText(0,poDes5);
	items.append(q);
	delete[] strchr1;

	p->insertChildren(0,items);
	return true;
}

bool GeometryCorrection::ShowGrayImage()
{
	//firstly show a gray image: base image ;
	//check if the file has been selected;
	if (treeBaseItem==treeWidget->currentItem())
	{
		//to show base image in gray;
		//firstly, show overview, creat a qimage;
		pShowimagebaseUI=new ShowImageBase1(0,pBaseFileDataset);
		connect(pShowimagebaseUI,SIGNAL(ReportPosition(QPoint)),this,SLOT(GetBasePosition(QPoint)));
		connect(this,SIGNAL(ReportCloseWindows()),pShowimagebaseUI,SLOT(close()));
		pShowimagebaseUI->ShowOverviewGray();
	} 
	return true;
}

bool GeometryCorrection::ShowColorImage()
{
	if (treeBaseItem==treeWidget->currentItem())
	{
		//to show base image in gray;
		//firstly, show overview, creat a qimage;
		pShowimagebaseUI=new ShowImageBase1(0,pBaseFileDataset);
		connect(pShowimagebaseUI,SIGNAL(ReportPosition(QPoint)),this,SLOT(GetBasePosition(QPoint)));
		pShowimagebaseUI->ShowOverviewColor(nRGBofBase);
	} 
	return true;
}

void GeometryCorrection::slotAddImage()
{
	if (radioButtonGray->isChecked())
		ShowGrayImage();
	if (radioButtonRgb->isChecked())
		ShowColorImage();
}

void GeometryCorrection::GetBasePosition(QPoint p)
{
	ReportBasePosition(p);
}

bool GeometryCorrection::InitUI()
{
	QWidget *centwig=new QWidget;
	setCentralWidget(centwig);
//	centwig->resize(50,100);
	treeWidget=new QTreeWidget();
	treeWidget->setHeaderLabel(tr("Image Info"));
	treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
	treeBaseItem=new QTreeWidgetItem(treeWidget);

	groupBox=new QGroupBox;
	groupBox->setTitle("Style");
	radioButtonGray=new QRadioButton("Gray");
	radioButtonRgb=new QRadioButton("Color");
	QHBoxLayout *layout3=new QHBoxLayout;
	layout3->addWidget(radioButtonGray);
	layout3->addWidget(radioButtonRgb);
	groupBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
	groupBox->setLayout(layout3);

	groupBox_2=new QGroupBox;
	radioButtonRed=new QRadioButton("Red");
	radioButtonGreen=new QRadioButton("Green");
	radioButtonBlue=new QRadioButton("Blue");
	lineEditRed=new QLineEdit;
	lineEditGreen=new QLineEdit;
	lineEditBlue=new QLineEdit;
	groupBox_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::MinimumExpanding);
	QGridLayout *layout1=new QGridLayout(groupBox_2);
	layout1->addWidget(radioButtonRed,0,0);
	layout1->addWidget(radioButtonGreen,1,0);
	layout1->addWidget(radioButtonBlue,2,0);
	layout1->addWidget(lineEditRed,0,1);
	layout1->addWidget(lineEditGreen,1,1);
	layout1->addWidget(lineEditBlue,2,1);
	
	QHBoxLayout *layout2=new QHBoxLayout;
	pushButtonCancel=new QPushButton;
	pushButtonCancel->setText(tr("Cancel"));
	pushButtonLoadImage=new QPushButton;
	pushButtonLoadImage->setText("LoadImage");
	layout2->addWidget(pushButtonLoadImage);
	layout2->addWidget(pushButtonCancel);

    layoutMain=new QVBoxLayout;
	layoutMain->addWidget(treeWidget);
	layoutMain->addWidget(groupBox);
	layoutMain->addWidget(groupBox_2);
	layoutMain->addLayout(layout2);

	centwig->setLayout(layoutMain);

	QDesktopWidget desktopwidg;
	const QRect screen=desktopwidg.screenGeometry(-1);
	move(screen.width()/2-200,screen.y());
	return true;
}

void GeometryCorrection::slotTreeClicked( QTreeWidgetItem * item, int column )
{
	//the number of selected raster band;
	for (int i=0;i<treeBaseLayerItem.count();i++)
	{
		if (treeBaseLayerItem.at(i)==treeWidget->currentItem())
		{
			//get the number of raster band;
			if(radioButtonRed->isChecked())
			{
				nRGBofBase[0]=i+1;
				radioButtonGreen->setChecked(true);
				lineEditRed->setText(QString("Layer %0").arg(i+1));
				break;
			}
			if (radioButtonGreen->isChecked())
			{
				nRGBofBase[1]=i+1;
				radioButtonBlue->setChecked(true);
				lineEditGreen->setText(QString("Layer %0").arg(i+1));
				break;
			}
			if (radioButtonBlue->isChecked())
			{
				nRGBofBase[2]=i+1;
				radioButtonRed->setChecked(true);
				lineEditBlue->setText(QString("Layer %0").arg(i+1));
				break;
			}
		}
	}

}

void GeometryCorrection::slotRadioGrayClicked()
{
	groupBox_2->setDisabled(true);
}

void GeometryCorrection::slotRadioColorClicked()
{
	groupBox_2->setEnabled(true);
	radioButtonRed->setChecked(true);
}

bool GeometryCorrection::CheckOverView(GDALDataset*pDataset)
{
	GDALRasterBand *pband=pDataset->GetRasterBand(1);
	int n=pband->GetOverviewCount();
	if (n==0)
	{
		BuildOverView(pDataset);
        QMessageBox w;
        w.setText("build over view for the image,please reopen it!");
        return false;
	}
	return true;
}

bool GeometryCorrection::BuildOverView(GDALDataset* poDataset)
{
	//abc.tif 2 4 8 16
	const char * pszResampling = "nearest";
	int          anLevels[1024];
	int          nLevelCount = 0;
	anLevels[nLevelCount++]=2;
	anLevels[nLevelCount++]=4;
	anLevels[nLevelCount++]=8;
	anLevels[nLevelCount++]=16;

	poDataset->BuildOverviews( pszResampling, 
		nLevelCount, anLevels, 0, NULL,
		GDALTermProgress, NULL );

	return true;
}

void GeometryCorrection::closeEvent(QCloseEvent *event)
{
    qApp->exit();
}
