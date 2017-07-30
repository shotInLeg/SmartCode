#include "smartcode.h"
#include "ui_smartcode.h"
#include <QSpacerItem>

SmartCode::SmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);

    QComboBox* cc = new QComboBox;
    cc->addItem("sum(a =Int, b =Int) =Int");
    cc->addItem("applicate(a =List, b =(Int, Int)Int) =List");
    cc->addItem("sort(a =List, b =(Int, Int)Bool) =List");

    ui->cbCurrentInstructionInfo->addItem("sum(a =Int, b =Int) =Int");
    ui->cbCurrentInstructionInfo->addItem("applicate(a =List, b =(Int, Int)Int) =List");
    ui->cbCurrentInstructionInfo->addItem("sort(a =List, b =(Int, Int)Bool) =List");

    ui->toolBar->addWidget(cc);
}

SmartCode::~SmartCode()
{
    delete ui;
}
