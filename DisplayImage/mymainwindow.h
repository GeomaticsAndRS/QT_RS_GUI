#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include "ui_mymainwindow.h"
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QTreeWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QString>
#include <QMessageBox>
#include <QLatin1String>
#include <QImage>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_core.h>
#include <math.h>
#include "showimagebase1.h"
#include "showimagebase2.h"

class MyMainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MyMainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MyMainWindow();

private:
	Ui::MyMainWindowClass ui;
	
 public:
	QString mBaseFileName;
	QTreeWidget *treeWidget;//ui items
	QTreeWidgetItem *treeBaseItem;
	QList<QTreeWidgetItem *> treeBaseLayerItem;
	QTreeWidgetItem *treeBaseMapinfoItem;
	QGroupBox   *groupBox,*groupBox_2;
	QRadioButton *radioButtonGray,*radioButtonRgb,*radioButtonBlue,*radioButtonGreen,*radioButtonRed;
	QLineEdit   *lineEditBlue,*lineEditGreen,*lineEditRed;
	QPushButton *pushButtonCancel,*pushButtonLoadImage;
	QVBoxLayout *layoutMain;

	int nRGBofBase[3];
	int nwidth,nheight;

	GDALDataset *pBaseFileDataset;//the dataset of two related files
	ShowImageBase1 *pShowimagebaseUI1;
	ShowImageBase2 *pShowimagebaseUI2;

public slots:
    void slotActionOpenBaseFile();
    void slotAddImage();
    void slotTreeClicked( QTreeWidgetItem * , int );
    void slotRadioGrayClicked();
    void slotRadioColorClicked();
    void closeEvent(QCloseEvent *);


public:
	bool InitUI();
	bool GetBaseFileMapinfo(QString);
	bool ShowGrayImage();
	bool ShowColorImage();
	bool CreatQimage(QImage*,GByte*);
	bool CheckOverView(GDALDataset*);
	bool BuildOverView(GDALDataset*);

public slots:
	void GetBasePosition(QPoint);

signals:
	void ReportBasePosition(QPoint);
	void ReportCloseWindows();
};

#endif // mymainwindow_H
