#include "smartcode.h"
#include "ui_smartcode.h"


void SmartCode::on_aCreateFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Создать файл..."), currentPath, tr("Archi Source File (*.arc)"));

    if(QFileInfo(dir).baseName() == QFileInfo(dir).fileName())
        dir += ".arc";

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    saveFile.write("//Created Source File by SmartCode");

    saveFile.close();

    updateTreeWidget();

    ui->swPages->setCurrentIndex(0);
}

void SmartCode::projectCreated(QString projectPath, QWidget* w)
{
    w->close();

    currentPath = projectPath;

    updateTreeWidget();

    ui->swPages->setCurrentIndex(0);
}

void SmartCode::createCancel(QWidget *w)
{
    w->close();
}

void SmartCode::on_aCreateProject_triggered()
{
    CreateProject * dialog = new CreateProject;
    dialog->show();

    connect(dialog, SIGNAL( createdDone(QString, QWidget*) ), this, SLOT( projectCreated(QString, QWidget*) ) );
    connect(dialog, SIGNAL( createdCancel(QWidget*)), this, SLOT( projectCreateCancel(QWidget*) ) );
}

void SmartCode::on_aOpenProject_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Открыть проект..."),"",tr("Archi Build File (*.abc)"));

    if(!file.contains(".abc"))
        return;

    QFileInfo openFile(file);

    currentPath = openFile.absoluteDir().absolutePath();

    updateTreeWidget();

    ui->swPages->setCurrentIndex(0);
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

    codeEditor->setPlainText( QString::fromStdString(bytesFromFile.toStdString()) );

    currentFile = dir;
    openFile.close();

    ui->swPages->setCurrentIndex(0);
}

void SmartCode::on_aSaveFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Сохранить файл..."),currentPath,tr("Archi Source File (*.arc)"));

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append(codeEditor->toPlainText()) );

    saveFile.close();
}

void SmartCode::on_aSave_triggered()
{
    QFile saveFile(currentFile);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append(codeEditor->toPlainText()) );

    saveFile.close();
}

void SmartCode::updateTreeWidget()
{
    ui->tvProjectStruct->clear();

    QDir dir(currentPath);

    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->tvProjectStruct);
    rootItem->setText(0, QFileInfo(currentPath).fileName() );
    ui->tvProjectStruct->addTopLevelItem(rootItem);

    printDir(dir, rootItem);
}

void SmartCode::printDir(const QDir &dir, QTreeWidgetItem * item )
{
    QFileInfoList dirContent = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i < dirContent.size(); i++)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);

        if( dirContent.at(i).isDir() )
        {
            QDir subDir(dirContent.at(i).absolutePath() + "/" + dirContent.at(i).fileName());
            subItem->setText(0, dirContent.at(i).fileName() );
            printDir(subDir, subItem);
        }
        else
        {
            subItem->setText(0, dirContent.at(i).fileName() );

            QFile openFile( dirContent.at(i).absolutePath() );
            if(!openFile.open(QIODevice::ReadOnly))
            {
                return;
            }
            QByteArray bytesFromFile = openFile.readAll();

            projectFiles.push_back( {dirContent.at(i).absolutePath(), bytesFromFile } );

            openFile.close();
        }
    }
}

