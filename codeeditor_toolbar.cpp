#include "smartcode.h"
#include "ui_smartcode.h"


void SmartCode::setupMainToolBar()
{
    runScript = new QComboBox(this);
    runScript->addItem("Лего");

    QToolBar * tbb = new QToolBar(this);
    tbb->setIconSize(QSize(16, 16));
    tbb->setStyleSheet("");

    tbb->addWidget(runScript);
    tbb->addAction(ui->aStart);
    tbb->addAction(ui->aStartDebuging);
    tbb->addAction(ui->aStop);

    ui->lCodeEditorInfo->addWidget(tbb);
}
