#include "smartcode.h"
#include "ui_smartcode.h"


#include "dialogs/s_create_new_entry/s_create_new_entry.h"
#include "dialogs/s_create_new_project/s_create_new_project.h"
#include "dialogs/s_check_unsave_changes/s_check_unsave_changes.h"

SmartCode::SmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);

    QComboBox* cc = new QComboBox;
    cc->addItem("sum(a =Int, b =Int) =Int");
    cc->addItem("applicate(a =List, b =(Int, Int)Int) =List");
    cc->addItem("sort(a =List, b =(Int, Int)Bool) =List");

    ui->cbCurrentInstructionInfo->addItem("sum(a =Int, b =Int) =Int");
    ui->cbCurrentInstructionInfo->addItem("applicate(a =List, b =(Int, Int)Int) =List");
    ui->cbCurrentInstructionInfo->addItem("sort(a =List, b =(Int, Int)Bool) =List");

    ui->toolBar->addWidget(cc);


    QComboBox* treeView = new QComboBox(this);
    treeView->addItem("Папка проекта");
    treeView->addItem("Струкрутра проекта");
    treeView->addItem("Структура файла");

    QToolBar* tb = new QToolBar(this);
    tb->setIconSize(QSize(16, 16));
    QTreeWidget* projectTree = new QTreeWidget(this);

    tb->addAction(ui->aAddFile);
    tb->addAction(ui->aDeleteFile);
    tb->addWidget(treeView);

    ui->lLeftBar->addWidget(tb);
    ui->lLeftBar->addWidget(projectTree);

    QString basePath = "/Users/shotinleg/";
    QVector<QPair<QString, QString> > types = {
        {"dir", "Папка"},
        {"aml_file", "AML файл"}
    };

    SCreateNewEntry* ce = new SCreateNewEntry(types, basePath, this);
    ce->show();


    QVector<QPair<QString, QString> > langs = {
        {"aml", "AML"},
        {"beria", "БЕРИЯ"}
    };

    QString baseInterpreterPath = "/usr/local/bin/";

    QVector<QPair<QString, QString> > projectTypes = {
        {"console", "Консольное приложение"},
        {"gui", "Графическое приложение"}
    };

    QString baseProjectPath = "/Users/shotinleg/";

    SCreateNewProject* cp = new SCreateNewProject(langs, baseInterpreterPath, projectTypes, baseProjectPath, this);
    cp->show();

    QVector<QString> unsaveFiles = {
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Sources/main.aml",
        "ProjectFolder/Interface/main.aml"
    };

    SCheckUnsaveChanges* cu = new SCheckUnsaveChanges(unsaveFiles, this);
    cu->show();
}

SmartCode::~SmartCode()
{
    delete ui;
}
