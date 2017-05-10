#include "SCreateNewEntry.h"
#include "ui_SCreateNewEntry.h"
#include <QDebug>

SCreateNewEntry::SCreateNewEntry(QString parentPath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCreateNewEntry)
{
    ui->setupUi(this);
    pPath = parentPath;
}

SCreateNewEntry::~SCreateNewEntry()
{
    delete ui;
}

void SCreateNewEntry::on_buttonBox_accepted()
{
    int type = ui->cbType->currentIndex();
    QString name = ui->eName->text();

    if( type == 0 )
    {
        QFile currentFile(pPath + name);
        if(currentFile.open(QIODevice::WriteOnly))
        {
            currentFile.write("");
            currentFile.close();

            emit entryCreated("file", name);
        }
        else
        {
            qDebug() << pPath << " " << pPath+"/"+name;

            QMessageBox::information(this,
                                     "Ошибка",
                                     "Во время создания файла произошла "
                                     "ошибка. Проверьте, что указанная "
                                     "папка существует и у приложения есть "
                                     "доступ на запись в нее.");
        }
    }
    else if( type == 1 )
    {
        QDir currentPath(pPath);
        if( currentPath.mkdir(name) )
            emit entryCreated("dir", name);
    }
}

void SCreateNewEntry::on_buttonBox_rejected()
{
    this->close();
}
