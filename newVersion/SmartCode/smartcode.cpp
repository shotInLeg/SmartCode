#include "smartcode.h"
#include "ui_smartcode.h"


#include "dialogs/s_create_new_entry/s_create_new_entry.h"
#include "dialogs/s_create_new_project/s_create_new_project.h"
#include "dialogs/s_check_unsave_changes/s_check_unsave_changes.h"
#include "dialogs/s_confirm_remove/s_confirm_remove.h"

SmartCode::SmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);



    QComboBox* cc = new QComboBox;
    cc->addItem("sum =Int(a =Int, b =Int)");
    cc->addItem("applicate =List(lst =List, aplicator =Int(Int, Int))");
    cc->addItem("sort =List(lst =List, predicat =Bool(Int, Int))");
    ui->toolBar->addWidget(cc);


    QComboBox * cei = new QComboBox(this);
    cei->addItem("sum =Int(a =Int, b =Int)");
    cei->addItem("applicate =List(lst =List, aplicator =Int(Int, Int))");
    cei->addItem("sort =List(lst =List, predicat =Bool(Int, Int))");

    QToolBar * tbb = new QToolBar(this);
    //tbb->setLayout(new QHBoxLayout());
    tbb->addWidget(cei);


    ui->lCodeEditorInfo->addWidget(tbb);





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

    QVector<QString> removeFiles = {
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

    SConfirmRemove* cr = new SConfirmRemove(removeFiles, this);
    cr->show();

}

SmartCode::~SmartCode()
{
    delete ui;
}
