#include "SSmartCode.h"
#include "ui_SSmartCode.h"

SSmartCode::SSmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SSmartCode)
{
    ui->setupUi(this);
    setupCodeEditor();
    setupTreeView();

    currentPath = "";
    currentFile = "";
}

SSmartCode::~SSmartCode()
{
    delete ui;
}

void SSmartCode::setupCodeEditor()
{
    codeEditor = new SCodeEditor();
    codeEditor->setObjectName("pteCodeEditor");
    codeEditor->setTabStopWidth ( 33 );
    codeEditor->setFont( QFont("Consolas", 11) );
    codeEditor->setStyleSheet("background: rgb(80,80,80); color: rgb(255, 255, 255); border: 0px solid black;");
    highlighter = new SHighlighter( codeEditor->document() );

    ui->codeEditorLayout->addWidget(codeEditor);
}

void SSmartCode::setupTreeView()
{
    dirModel = new QDirModel();
    dirModel->removeColumn(0);
}

void SSmartCode::updateTreeView()
{
    ui->tvProjectFiles->clear();

    QDir dir(currentPath);

    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->tvProjectFiles);
    rootItem->setText(0, QFileInfo(currentPath).fileName() );
    ui->tvProjectFiles->addTopLevelItem(rootItem);
    printDir(dir, rootItem);
}

void SSmartCode::printDir(const QDir &dir, QTreeWidgetItem *item)
{
    QFileInfoList dirContent = dir.entryInfoList(QDir::Files |
                                                 QDir::Dirs |
                                                 QDir::NoDotAndDotDot);

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
        }
    }
}

QString SSmartCode::dreelUp(QTreeWidgetItem *item)
{
    QString path = "";
    QTreeWidgetItem * parent = item;
    int i = 0;
    while(parent->parent())
    {
        if( i == 0 )
            path = parent->text(0);
        else
            path = parent->text(0) + "/" + path;

        parent = parent->parent();
        i++;
    }


    return path;
}

void SSmartCode::on_bAddFile_clicked()
{
    QString selectedPath = dreelUp(ui->tvProjectFiles->currentItem());
    SCreateNewEntry * newEntry =
            new SCreateNewEntry(currentPath + "/" + selectedPath);

    connect(newEntry, SIGNAL(entryCreated(QString,QString)),
            this, SLOT(entryCreated(QString,QString)));

    newEntry->show();
}

void SSmartCode::on_tvProjectFiles_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    qDebug() << currentPath + "/" + dreelUp(item);

    QFile openFile( currentPath + "/" + dreelUp(item) );
    if(!openFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл для четния, "
                                                 "проверьте права доступа");
    }

    QByteArray bytesFromFile = openFile.readAll();

    codeEditor->setPlainText( QString::fromStdString(bytesFromFile.toStdString()) );

    currentFile = currentPath + "/" + dreelUp(item);
    openFile.close();
}

void SSmartCode::on_aOpenProject_triggered()
{
    currentPath = QFileDialog::getExistingDirectory(this,
                                                    "Открыть проект",
                                                    "~");
    updateTreeView();
}
