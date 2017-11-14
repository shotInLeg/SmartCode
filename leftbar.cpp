#include "smartcode.h"
#include "ui_smartcode.h"


// Slots


void SmartCode::on_twProjectTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(treeWidgetFiles.contains(item))
    {
        QFileInfo info(treeWidgetFiles[item]);
        if(info.isDir()) {
            return;
        }

        SCodeEditor* ce = openTab(item->text(column), treeWidgetFiles[item]);
        viewFileInCodeArea(ce, treeWidgetFiles[item]);
        codeEditorFiles[ce] = treeWidgetFiles[item];

        QObject::connect(ce, SIGNAL(changed(SCodeEditor*)),
                         this, SLOT(codeEditorChanged(SCodeEditor*)));
        QObject::connect(ce, SIGNAL(destroyed(QObject*)),
                         ce, SLOT(deleteLater()));
    }
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
        item->setIcon(0, QIcon(":/icons/resources/icons/dir_opened.png"));
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

        treeWidgetFiles[subItem] = subDir.absolutePath();
        recoursiveShowDirTree(subDir, subItem);
    }

    for(const QFileInfo& file : files)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);
        subItem->setIcon(0, QIcon(":/icons/resources/icons/source_code.png"));
        subItem->setText(0, file.fileName() );
        treeWidgetFiles[subItem] = file.filePath();
    }
}
