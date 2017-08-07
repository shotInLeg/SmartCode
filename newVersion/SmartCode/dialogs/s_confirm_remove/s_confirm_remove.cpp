#include "s_confirm_remove.h"
#include "ui_s_confirm_remove.h"

SConfirmRemove::SConfirmRemove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SConfirmRemove)
{
    ui->setupUi(this);
}

SConfirmRemove::~SConfirmRemove()
{
    delete ui;
}
