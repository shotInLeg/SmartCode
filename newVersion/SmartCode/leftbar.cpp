#include "smartcode.h"
#include "ui_smartcode.h"


// Slots


void SmartCode::on_twProjectTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    openTab(item->text(column));
}


// Function

void SmartCode::showDirTree(const QString &dirPath)
{
    ui->twProjectTree->clear();
    recoursiveShowDirTree(QDir(dirPath));
}

void SmartCode::recoursiveShowDirTree(const QDir &startDir, QTreeWidgetItem *item)
{
    if(item == nullptr)
    {
        item = new QTreeWidgetItem(ui->twProjectTree);
        item->setIcon(0, QIcon(":/icons/resources/icons/dir_closed.png"));
        item->setText(0, startDir.dirName());
        ui->twProjectTree->addTopLevelItem(item);
    }

    QFileInfoList files = startDir.entryInfoList(QDir::Files |
                                                 QDir::Dirs |
                                                 QDir::NoDotAndDotDot);

    QFileInfoList dirs;
    for(int i = 0; i < files.size(); i++)
    {
        if(files.at(i).isDir())
        {
            dirs.push_back(files.at(i));
            files.removeAt(i);
            i--;
        }
    }

    for(const QFileInfo& dir : dirs)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);
        QDir subDir(dir.absolutePath() + "/" + dir.fileName());

        subItem->setIcon(0, QIcon(":/icons/resources/icons/dir_closed.png"));
        subItem->setText(0, dir.fileName());

        recoursiveShowDirTree(subDir, subItem);
    }

    for(const QFileInfo& file : files)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);
        subItem->setIcon(0, QIcon(":/icons/resources/icons/source_code.png"));
        subItem->setText(0, file.fileName() );
    }
}
