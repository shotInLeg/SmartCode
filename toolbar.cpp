#include "smartcode.h"
#include "ui_smartcode.h"

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
