#include "difficultyselector.h"
#include "ui_difficultyselector.h"

difficultyselector::difficultyselector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::difficultyselector)
{
    ui->setupUi(this);
}

difficultyselector::~difficultyselector()
{
    delete ui;
}

void difficultyselector::on_PlayButton_clicked()
{
    emit playGame(ui->difficultyBox->value());
    this->hide();
}

void difficultyselector::on_difficultyselector_finished(int result)
{
    emit playGame(1);
}
