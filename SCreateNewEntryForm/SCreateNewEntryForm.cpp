#include "SCreateNewEntryForm.h"
#include "ui_SCreateNewEntryForm.h"

SCreateNewEntryForm::SCreateNewEntryForm(const QString &parentPath,
                                         QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCreateNewEntryForm)
{
    ui->setupUi(this);
    this->parentPath = parentPath;
}

SCreateNewEntryForm::~SCreateNewEntryForm()
{
    delete ui;
}

void SCreateNewEntryForm::on_buttonBox_accepted()
{
    int type = ui->cbType->currentIndex();
    QString name = ui->eName->text();

    if( type == 0 )
    {
        QFile currentFile(parentPath + name);
        if(currentFile.open(QIODevice::WriteOnly))
        {
            currentFile.write("");
            currentFile.close();

            emit entryCreated("file", name);
        }
        else
        {
            qDebug() << parentPath << " " << parentPath+"/"+name;

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
        QDir currentPath(parentPath);
        if( currentPath.mkdir(name) )
            emit entryCreated("dir", name);
    }
}

void SCreateNewEntryForm::on_buttonBox_rejected()
{
    this->close();
}
