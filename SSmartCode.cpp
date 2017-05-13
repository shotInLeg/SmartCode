#include "SSmartCode.h"
#include "ui_SSmartCode.h"

SSmartCode::SSmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SSmartCode)
{
    ui->setupUi(this);
    setupCodeEditor();
    setupTreeView();
    setupRightBar();
    setupBottomBar();
    setupLeftBar();

    currentPath = "";
    currentFile = "";

    codeEditorPos = new QLabel("0|0");
    ui->statusBar->addWidget(codeEditorPos);
}

SSmartCode::~SSmartCode()
{
    delete ui;
}



