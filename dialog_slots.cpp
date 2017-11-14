#include "smartcode.h"
#include "ui_smartcode.h"

void SmartCode::saveFiles(QVector<QString> files)
{
    Q_UNUSED(files);
}

void SmartCode::notSaveFiles(QVector<QString> files)
{
    Q_UNUSED(files);
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

void SmartCode::createEntry(QString type, QString path, QString name)
{
    if(type == "*") {
        QDir(path).mkdir(name);
    } else {
        QFile newFile(path + "/" + name);
        if(!newFile.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, "Ошибка", "Не удалось открыть файл "
                                                     "для четния, проверьте "
                                                     "права доступа");
            return;
        }
        newFile.close();
    }

    showDirTree(projectPath);
}

void SmartCode::createProject(QString lang, QString interpreterPath, QString projectType, QString projectPath, QString projectName)
{
    Q_UNUSED(lang);
    Q_UNUSED(interpreterPath);
    Q_UNUSED(projectType);

    QDir(projectPath).mkdir(projectName);

    this->projectPath = projectPath + "/" + projectName;
    showDirTree(this->projectPath);
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
