#include "SSmartCode.h"
#include "ui_SSmartCode.h"

void SSmartCode::projectCreated(QString path)
{
    currentPath = path;
    updateTreeView();
    ui->wLeftSide->show();
    ui->aProjectTree->setChecked(true);
}

void SSmartCode::entryCreated(QString type, QString name)
{
    Q_UNUSED(type);
    Q_UNUSED(name);

    updateTreeView();
}

void SSmartCode::codeEditorPosChanged()
{
    int col = codeEditor->textCursor().columnNumber();
    int row = codeEditor->textCursor().blockNumber()+1;

    codeEditorPos->setText(QString::number(row) +
                           "|" + QString::number(col));
}

void SSmartCode::currentFileChanged()
{
    if(currentFile == "")
        return;

    if(!unsavesFiles.contains(currentFile))
    {
        unsavesFiles.push_back(currentFile);
        qDebug() << "File" << currentFile << "add to unsaved";
    }
}

void SSmartCode::saveAndClose()
{
    cashCurrentDocument();

    for(auto file = unsavesFiles.begin(); file != unsavesFiles.end(); file++)
    {

        QFile saveFile(*file);
        if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            saveFile.write(cashedFiles[*file]);
        }
        saveFile.close();
    }

    unsavesFiles.clear();
    cashedFiles.clear();

    this->close();
}

void SSmartCode::notSaveAndClose()
{
    unsavesFiles.clear();
    cashedFiles.clear();
    this->close();
}
