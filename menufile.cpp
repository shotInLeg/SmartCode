#include "smartcode.h"
#include "ui_smartcode.h"


void SmartCode::on_aCreateFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Создать файл..."),currentPath,tr("Archi Source File (*.arc)"));

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write("");

    saveFile.close();
}

void SmartCode::on_aCreateProject_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Создать проект..."),"",tr("Archi Build File (*.abc)"));
    QFileInfo openFile(file);

    qDebug() << openFile.fileName();

    QDir dir = openFile.absoluteDir();
    dir.mkdir( openFile.baseName() );
    dir.cd( openFile.baseName() );


    QFile saveFile(dir.absoluteFilePath(openFile.fileName()));
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append("["+openFile.baseName()+"]") );

    saveFile.close();
}

void SmartCode::on_aOpenProject_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Открыть проект..."),"",tr("Archi Build File (*.abc)"));

    QFileInfo openFile(file);

    qDebug() <<  openFile.absoluteDir().absolutePath() << openFile.absolutePath() << openFile.path();

    currentPath = openFile.absoluteDir().absolutePath();
    ui->tvProjectStruct->setRootIndex(dirModel->index(currentPath));
}


void SmartCode::on_aOpenFile_triggered()
{
    QString dir = QFileDialog::getOpenFileName(this, tr("Открыть файл..."),currentPath,tr("Archi Source File (*.arc)"));

    QFile openFile(dir);
    if(!openFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray bytesFromFile = openFile.readAll();

    ui->pteCodeEdit->setPlainText( QString::fromStdString(bytesFromFile.toStdString()) );

    currentFile = dir;
    openFile.close();
}

void SmartCode::on_aSaveFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Сохранить файл..."),currentPath,tr("Archi Source File (*.arc)"));

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append(ui->pteCodeEdit->toPlainText()) );

    saveFile.close();
}

void SmartCode::on_aSave_triggered()
{
    QFile saveFile(currentFile);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append(ui->pteCodeEdit->toPlainText()) );

    saveFile.close();
}

