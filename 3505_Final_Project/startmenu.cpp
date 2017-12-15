#include "startmenu.h"
#include "ui_startmenu.h"

startmenu::startmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startmenu)
{
    ui->setupUi(this);
}

startmenu::~startmenu()
{
    delete ui;
}
