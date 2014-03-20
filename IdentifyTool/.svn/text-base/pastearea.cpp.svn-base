#include "pastearea.h"
#include "ui_pastearea.h"

PasteArea::PasteArea(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::PasteArea)
{
    ui->setupUi(this);
    setWindowTitle("Paste Area");
    resize(150,200);
}

PasteArea::~PasteArea()
{
    delete ui;
}
