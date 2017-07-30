#include "SSmartCode.h"
#include "ui_SSmartCode.h"

//File Manage Panel
void SSmartCode::on_bAddFile_clicked()
{
    if( ui->tvProjectFiles->currentItem() == NULL )
    {
        QMessageBox::information(this, "Ошибка", "Чтобы добавить файл"
                                                 " в проект, его необходимо "
                                                 "открыть или создать");
        return;
    }

    QString selectedPath = dreelUp(ui->tvProjectFiles->currentItem());
    SCreateNewEntryForm * newEntry =
            new SCreateNewEntryForm(currentPath + "/" + selectedPath);

    connect(newEntry, SIGNAL(entryCreated(QString,QString)),
            this, SLOT(entryCreated(QString,QString)));

    newEntry->show();
}

//Project Tree View
void SSmartCode::on_tvProjectFiles_itemDoubleClicked(QTreeWidgetItem *item,
                                                     int column)
{
    Q_UNUSED(column);

    cashCurrentDocument();

    QString projectFile = currentPath + "/" + dreelUp(item);
    setHighlightPage(projectFile);


    if(cashedFiles.contains(projectFile))
    {
        codeEditor->setPlainText(QString(cashedFiles[projectFile]));
    }
    else
    {
        loadFileToCodeEditor(projectFile);
    }

    currentFile = projectFile;
}


