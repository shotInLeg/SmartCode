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

    QString projectFile = dreelUp(item);
    QFile openFile( currentPath + "/" + projectFile );
    if(!openFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл "
                                                 "для четния, проверьте "
                                                 "права доступа");
    }

    QByteArray bytesFromFile = openFile.readAll();

    QStringList partOfNameFile = projectFile.split(".");
    if(partOfNameFile.size() > 0)
    {
        QString type = partOfNameFile[partOfNameFile.size()-1];
        try
        {
            highlighter->updateHighlightRules(":/highlighter/SHighlighter/"
                                              ""+type+".hp");
        }
        catch(std::invalid_argument& ex)
        {
            qDebug() << "Не удалось подсветить синтаксис" << ex.what();
        }
    }
    codeEditor->setPlainText(QString(bytesFromFile));

    currentFile = currentPath + "/" + dreelUp(item);
    openFile.close();
}
