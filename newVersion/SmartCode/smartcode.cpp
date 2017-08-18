#include "smartcode.h"
#include "ui_smartcode.h"
#include <QDebug>


#include "dialogs/s_create_new_entry/s_create_new_entry.h"
#include "dialogs/s_create_new_project/s_create_new_project.h"
#include "dialogs/s_check_unsave_changes/s_check_unsave_changes.h"
#include "dialogs/s_confirm_remove/s_confirm_remove.h"
#include "dialogs/s_add_new_entry/s_add_new_entry.h"
#include "dialogs/s_git_commit/s_git_commit.h"

SmartCode::SmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);
    QFontDatabase::addApplicationFont(":/fonts/resources/fonts/FiraSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/fonts/FiraSans-SemiBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/fonts/FiraSans-Italic.ttf");

    QComboBox * cei = new QComboBox(this);
    cei->addItem("main() =Int");
    cei->addItem("Cell.new() =Cell");
    cei->addItem("Cell.new(x, y, status) =Cell(UInt, UInt, <!Int == 0 || Int == 1!>)");
    cei->addItem("Point.sum() =Double");

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

    tb->addAction(ui->aAddFile);
    tb->addAction(ui->aDeleteFile);
    tb->addWidget(treeView);

    ui->lLeftBarToolBar->addWidget(tb);

    QString basePath = "/Users/shotinleg/";
    QVector<QPair<QString, QString> > types = {
        {"*", "Папка"},
        {"*.aml", "AML файл"}
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

    SCreateNewProject* cp = new SCreateNewProject(langs,
                                                  baseInterpreterPath,
                                                  projectTypes,
                                                  baseProjectPath,
                                                  this);
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

    SAddNewEntry* ane = new SAddNewEntry(types, basePath, this);
    ane->show();



    QVector<QPair<QString, QString> > untrackedFiles = {
        {"new", "ProjectFolder/Sources/1.txt"},
        {"modified", "ProjectFolder/Sources/2.txt"},
        {"modified", "ProjectFolder/Sources/3.txt"},
        {"new", "ProjectFolder/Sources/4.txt"},
        {"modified", "ProjectFolder/Sources/5.txt"},
        {"new", "ProjectFolder/Sources/6.txt"},
        {"modified", "ProjectFolder/Sources/7.txt"},
        {"new", "ProjectFolder/Sources/8.txt"},
        {"modified", "ProjectFolder/Sources/9.txt"},
        {"new", "ProjectFolder/Sources/10.txt"}
    };

    QVector<QPair<QString, QString> > trackedFiles = {
        {"modified", "ProjectFolder/Sources/11.txt"},
        {"new", "ProjectFolder/Sources/12.txt"}
    };


    SGitCommit* gc = new SGitCommit(untrackedFiles, trackedFiles, this);
    gc->show();

    showDirTree("/Users/shotinleg/Documents/Projects/SmartCode/GameOfLife");
}

SmartCode::~SmartCode()
{
    delete ui;
}

QAbstractItemModel *SmartCode::modelFromFile(const QString &fileName, QCompleter *completer)
{
    QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
            return new QStringListModel(completer);

    #ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    #endif
        QStringList words;

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            if (!line.isEmpty())
                words << line.trimmed();
        }

    #ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
    #endif
        return new QStringListModel(words, completer);
}

void SmartCode::codeEditorClosed(SCodeEditor *ce, const QString &data)
{
    QString path = codeEditorFiles[ce];
    if(unsavedFiles.contains(path))
    {

    }
}

