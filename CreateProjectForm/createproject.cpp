#include "createproject.h"
#include "ui_createproject.h"

CreateProject::CreateProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateProject)
{
    ui->setupUi(this);
}

CreateProject::~CreateProject()
{
    delete ui;
}

void CreateProject::on_tbSelectPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Выберете папку"), "");

    ui->eProjectPath->setText(dir);


}

void CreateProject::on_bCreate_clicked()
{
    QString name = ui->eProjectName->text();
    QString dirPath = ui->eProjectPath->text();

    QDir dir(dirPath);
    dir.mkdir( name );
    dir.cd( name );

    QFile proFile(dir.absolutePath()+"/"+name+".abc");
    if(!proFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    proFile.write( QByteArray().append("["+name+"]") );

    QFile mainFile(dir.absolutePath()+"/main.arc");
    if(!mainFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    mainFile.write( QByteArray().append("//main file") );


    QString currentPath = dir.absolutePath();

    proFile.close();
    mainFile.close();

    emit createdDone(currentPath, this);
}

void CreateProject::on_bCancel_clicked()
{
    emit createdCancel(this);
}
