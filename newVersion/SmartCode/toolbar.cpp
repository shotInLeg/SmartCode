#include "smartcode.h"
#include "ui_smartcode.h"

void SmartCode::setupMainToolBar()
{
    runScript = new QComboBox(this);
    runScript->addItem("LegoLang");
    runScript->addItem("Python");
    runScript->addItem("БЕРИЯ");

    QToolBar * tbb = new QToolBar(this);
    tbb->setIconSize(QSize(16, 16));
    tbb->setStyleSheet("");

    tbb->addWidget(runScript);
    tbb->addAction(ui->aStart);
    tbb->addAction(ui->aStartDebuging);
    tbb->addAction(ui->aStop);

    ui->lCodeEditorInfo->addWidget(tbb);
}

void SmartCode::on_aSaveCurrentFile_triggered()
{
    SCodeEditor* w = dynamic_cast<SCodeEditor*>(ui->twOpenedFiles->currentWidget());

    QString path = "";
    if(codeEditorFiles.contains(w))
    {
        path = codeEditorFiles[w];
    }

    if(unsavedFiles.contains(path))
    {
        unsavedFiles.removeOne(path);
        saveDataFromCodeArea(w, path);
    }
}
