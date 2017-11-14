#include "smartcode.h"
#include "ui_smartcode.h"

#include "dialogs/s_create_new_entry/s_create_new_entry.h"


void SmartCode::setupProjectToolBar()
{
    QToolBar* tb = new QToolBar(this);
    tb->setIconSize(QSize(16, 16));

    QComboBox* treeView = new QComboBox(this);
    treeView->addItem("Папка проекта");
    treeView->addItem("Струкрутра проекта");
    treeView->addItem("Структура файла");

    tb->addAction(ui->aAddFile);
    tb->addAction(ui->aDeleteFile);
    tb->addWidget(treeView);

    ui->lLeftBarToolBar->addWidget(tb);
}

void SmartCode::on_aAddFile_triggered()
{
    QVector<QPair<QString, QString> > types = {
        {"*.lgc", "ЛегоКод файл"},
        {"*", "Папка"}
    };

    SCreateNewEntry* ce = new SCreateNewEntry(types, projectPath, this);
    ce->show();

    QObject::connect(ce, SIGNAL(createEntry(QString,QString,QString)),
                     this, SLOT(createEntry(QString,QString,QString)));
}

void SmartCode::on_aDeleteFile_triggered()
{
    QTreeWidgetItem* item = ui->twProjectTree->currentItem();
    if(treeWidgetFiles.contains(item))
    {
        QFileInfo info(treeWidgetFiles[item]);
        if(info.isDir()) {
            QString dirPath = treeWidgetFiles[item];
            QDir(dirPath).removeRecursively();
        } else {
            QString filePath = treeWidgetFiles[item];
            QFile(filePath).remove();
        }

        showDirTree(projectPath);
    }
}
