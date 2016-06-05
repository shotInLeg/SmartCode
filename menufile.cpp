#include "smartcode.h"
#include "ui_smartcode.h"


void SmartCode::on_aCreateFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Создать файл..."), currentPath, tr("Archi Source File (*.arc)"));

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write("//Created by SmartCode");

    saveFile.close();

    updateTreeWidget();
}

void SmartCode::on_aCreateProject_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Создать проект..."), "", tr("Archi Build File (*.abc)"));
    QFileInfo openFile(file);


    QDir dir = openFile.absoluteDir();
    dir.mkdir( openFile.baseName() );
    dir.cd( openFile.baseName() );


    QFile saveFile(dir.absoluteFilePath(openFile.fileName()));
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append("["+openFile.baseName()+"]") );


    currentPath = QFileInfo(saveFile).absolutePath();

    saveFile.close();

    updateTreeWidget();
}

void SmartCode::on_aOpenProject_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Открыть проект..."),"",tr("Archi Build File (*.abc)"));

    QFileInfo openFile(file);

    currentPath = openFile.absoluteDir().absolutePath();

    updateTreeWidget();
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

void SmartCode::updateTreeWidget()
{
    ui->tvProjectStruct->clear();

    qDebug() << currentPath;

    QDir dir(currentPath);

    qDebug() << QFileInfo(currentPath).fileName() << dir.absolutePath();

    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->tvProjectStruct);
    rootItem->setText(0, QFileInfo(currentPath).fileName() );
    ui->tvProjectStruct->addTopLevelItem(rootItem);

    printDir(dir, rootItem);

    //qDebug() << index;
}

void SmartCode::printDir(const QDir &dir, QTreeWidgetItem * item )
{
    QFileInfoList dirContent = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);



    for(int i = 0; i < dirContent.size(); i++)
    {
        if( dirContent.at(i).isDir() )
            qDebug() << "DIR" << " >>>> " << dirContent.at(i).absolutePath() + "/" + dirContent.at(i).fileName();
        else
            qDebug() << "FILE" << " >>>> " << dir.absolutePath() << ">>" << dirContent.at(i).fileName();
    }

    for(int i = 0; i < dirContent.size(); i++)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);

        if( dirContent.at(i).isDir() )
        {
            //qDebug() << "if dir >>>>" << dirContent.at(i).path();

            QDir subDir(dirContent.at(i).absolutePath() + "/" + dirContent.at(i).fileName());
            subItem->setText(0, dirContent.at(i).fileName() );
            printDir(subDir, subItem);
        }
        else
        {
            subItem->setText(0, dirContent.at(i).fileName() );
        }
    }
}

