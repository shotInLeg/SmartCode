#include "smartcode.h"
#include "ui_smartcode.h"

void SmartCode::saveFiles(QVector<QString> files)
{

}

void SmartCode::notSaveFiles(QVector<QString> files)
{

}

void SmartCode::closeTabSave(QVector<QString> files)
{
    for(const QString& path : files)
    {
        SCodeEditor * ce = nullptr;
        for(auto it = codeEditorFiles.begin(); it != codeEditorFiles.end(); it++)
        {
            if(it.value() == path)
            {
                ce = it.key();
                break;
            }
        }

        if(ce != nullptr)
        {
            saveDataFromCodeArea(ce, path);
            unsavedFiles.removeOne(path);

            for(int tabIndex = 0; tabIndex < ui->twOpenedFiles->count(); tabIndex++)
            {
                if(ce == ui->twOpenedFiles->widget(tabIndex))
                {
                    ui->twOpenedFiles->removeTab(tabIndex);
                    break;
                }
            }
        }
    }
}

void SmartCode::closeTabNotSave(QVector<QString> files)
{
    for(const QString& path : files)
    {
        SCodeEditor * ce = nullptr;
        for(auto it = codeEditorFiles.begin(); it != codeEditorFiles.end(); it++)
        {
            if(it.value() == path)
            {
                ce = it.key();
                break;
            }
        }

        if(ce != nullptr)
        {
            unsavedFiles.removeOne(path);

            for(int tabIndex = 0; tabIndex < ui->twOpenedFiles->count(); tabIndex++)
            {
                if(ce == ui->twOpenedFiles->widget(tabIndex))
                {
                    ui->twOpenedFiles->removeTab(tabIndex);
                    break;
                }
            }
        }
    }
}

void SmartCode::codeEditorChanged(SCodeEditor *ce)
{
    QString path = "";
    if(codeEditorFiles.contains(ce))
    {
        path = codeEditorFiles[ce];
    }

    if(!path.isEmpty())
    {
        unsavedFiles.removeOne(path);
        unsavedFiles.push_back(path);
    }

    qDebug() << unsavedFiles;
}
