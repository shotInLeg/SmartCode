#include "SSaveChangesForm.h"
#include "ui_SSaveChangesForm.h"

SSaveChangesForm::SSaveChangesForm(const QVector<QString> &files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSaveChangesForm)
{
    ui->setupUi(this);

    for(auto it = files.begin(); it != files.end(); it++)
    {
        ui->lwFiles->addItem(*it);
    }
}

SSaveChangesForm::~SSaveChangesForm()
{
    delete ui;
}

void SSaveChangesForm::on_bSave_clicked()
{
    emit save();
    this->close();
}

void SSaveChangesForm::on_bNotSave_clicked()
{
    emit notSave();
    this->close();
}

void SSaveChangesForm::on_bCancel_clicked()
{
    this->close();
}
