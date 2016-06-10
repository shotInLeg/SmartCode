#include "smartcode.h"
#include "ui_smartcode.h"

SmartCode::SmartCode(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);
    setupCodeEditor();

    ui->textBoxLayout->addWidget(codeEditor);

    currentPath = "";
    currentFile = "";
    dirModel = new QDirModel();
    dirModel->removeColumn(0);

    QPushButton * bMake = new QPushButton("Собрать C++");
    ui->mainToolBar->addWidget(bMake);
    connect(bMake, SIGNAL(clicked(bool)), this, SLOT(on_aMakeCPP_triggered()));


    //ui->mainToolBar->setStyleSheet("background-color: rgb(79, 79, 79); color: rgb(255, 255, 255);");


    //updateTreeWidget();
}

SmartCode::~SmartCode()
{
    delete ui;
}

void SmartCode::setupCodeEditor()
{
    codeEditor = new CodeEditor();
    codeEditor->setObjectName("pteCodeEditor");
    codeEditor->setTabStopWidth ( 33 );
    codeEditor->setFont( QFont("Consolas", 11) );
    codeEditor->setStyleSheet("color: rgb(255, 255, 255); border: 0px solid black;");
    highlighter = new Highlighter( codeEditor->document() );
}


void SmartCode::on_aFontSettings_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, codeEditor->font(), this);
    if (ok)
    {
        codeEditor->setFont( font );
    }
}

void SmartCode::on_aMakeCPP_triggered()
{
    QFileInfo curFile(currentFile);
    QDir curDir(currentPath);
    QString projectName = curDir.dirName();

    curDir.cd("..");
    curDir.mkpath(projectName + "_cpp/Archi/ATL");
    curDir.mkpath(projectName + "_cpp/Archi/ACL");
    curDir.cd(projectName + "_cpp");

    QVector<QString> types;
    types.push_back( ":/archi/include/types/Archi/ATL/anum16.h" );
    types.push_back( ":/archi/include/types/Archi/ATL/anum16.cpp" );
    types.push_back( ":/archi/include/types/Archi/ATL/abit.h" );
    types.push_back( ":/archi/include/types/Archi/ATL/abit.cpp" );
    types.push_back( ":/archi/include/types/Archi/ATL/abyte.h" );
    types.push_back( ":/archi/include/types/Archi/ATL/abyte.cpp" );
    types.push_back( ":/archi/include/types/Archi/ATL/acharacsii.h" );
    types.push_back( ":/archi/include/types/Archi/ATL/acharascii.cpp" );
    types.push_back( ":/archi/include/types/Archi/ATL/abool.h" );
    types.push_back( ":/archi/include/types/Archi/ATL/abool.cpp" );

    for( int i = 0; i < types.size(); i++ )
    {
        QFile fileType (types[i]);

        if( fileType.open(QIODevice::ReadOnly) )
        {
            QFileInfo type_file_info(fileType);
            QByteArray type_file = fileType.readAll();

            qDebug() << ">>>>>>>>" << type_file_info.fileName();

            QFile saveTypeFile( curDir.absolutePath()+"/Archi/ATL/"+type_file_info.fileName() );
            if(!saveTypeFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                return;
            }
            saveTypeFile.write( type_file );

            saveTypeFile.close();
        }

        fileType.close();
    }


    QVector<QString> containers;
    containers.push_back( ":/archi/include/containers/Archi/ACL/aaray.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/aaray.cpp" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/acl.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/acontainer_functions.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/aexception.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/aiterator.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/aiterator_functions.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/array.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/asize.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/container_data.h" );
    containers.push_back( ":/archi/include/containers/Archi/ACL/matrix.h" );

    for( int i = 0; i < containers.size(); i++ )
    {
        QFile fileContainer (containers[i]);

        if( fileContainer.open(QIODevice::ReadOnly) )
        {
            QFileInfo container_file_info(fileContainer);
            QByteArray container_file = fileContainer.readAll();

            qDebug() << ">>>>>>>>" << container_file_info.fileName();

            QFile saveContainerFile( curDir.absolutePath()+"/Archi/ACL/"+container_file_info.fileName() );
            if(!saveContainerFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                return;
            }
            saveContainerFile.write( container_file );

            saveContainerFile.close();
        }

        fileContainer.close();
    }


    QString textFile = codeEditor->toPlainText();

    ACP parser;
    QVector< QPair<QString, QString> > tokens = parser.parse(textFile);

    QByteArray cppFile;
    /*for(int i = 0; i < tokens.size(); i++)
    {
        cppFile.append( tokens.at(i).second+"\n" );
        qDebug() << tokens.at(i).first<< ":" <<tokens.at(i).second;
    }*/
    cppFile.append( parser.parseString(textFile) );

    QFile saveFile(curDir.absolutePath()+"/"+curFile.baseName()+".cpp");
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( cppFile );

    saveFile.close();
}

void SmartCode::on_tvProjectStruct_doubleClicked(const QModelIndex &index)
{

}

void SmartCode::on_tvProjectStruct_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << currentPath + "/" + item->text(column);

    QFile openFile( currentPath + "/" + item->text(column) );
    if(!openFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray bytesFromFile = openFile.readAll();

    codeEditor->setPlainText( QString::fromStdString(bytesFromFile.toStdString()) );

    currentFile = currentPath + "/" + item->text(column);
    openFile.close();
}

void SmartCode::on_bCreateProject_clicked()
{
    on_aCreateProject_triggered();
}

void SmartCode::on_bOpenProject_clicked()
{
    on_aOpenProject_triggered();
}
