#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QToolBar>
#include <QTreeWidget>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>
#include <QAbstractItemModel>
#include <QStringListModel>

#include <QTextEdit>

#include <QDir>
#include <QFileInfoList>
#include <QFont>
#include <QFontDatabase>
#include <QMessageBox>
#include <QSpacerItem>

#include <QFileDialog>

#include "widgets/s_code_editor/s_code_editor.h"
#include "widgets/s_highlighter/s_highlighter.h"

namespace Ui {
class SmartCode;
}

class SmartCode : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartCode(QWidget *parent = 0);
    ~SmartCode();

private slots:
    void on_twProjectTree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_twOpenedFiles_tabCloseRequested(int index);

private:
    void setupMainToolBar();
    void setupProjectToolBar();
    void setupFonts();

    void showDirTree(const QString& dirPath);
    void recoursiveShowDirTree(const QDir& dir,
                               QTreeWidgetItem *item = nullptr);

    SCodeEditor *openTab(const QString& tabName, const QString &filePath);
    void viewFileInCodeArea(SCodeEditor *editor, const QString& filePath);
    void saveDataFromCodeArea(SCodeEditor *editor, const QString& filePath);

    QAbstractItemModel *modelFromFile(const QString& fileName, QCompleter* completer);

    void viewAllDialogs();

private slots:
    void codeEditorClosed(SCodeEditor* ce, const QString& data);
    void saveFiles(QVector<QString> files);
    void notSaveFiles(QVector<QString> files);

    void closeTabSave(QVector<QString> files);
    void closeTabNotSave(QVector<QString> files);

    void createEntry(QString type, QString path, QString name);
    void createProject(QString lang, QString interpreterPath,
                       QString projectType, QString projectPath,
                       QString projectName);

    void codeEditorChanged(SCodeEditor* ce);

    void on_aSaveCurrentFile_triggered();

    void on_aOpenProject_triggered();

    void on_aAddFile_triggered();

    void on_aCreateProject_triggered();

    void on_aDeleteFile_triggered();

private:
    Ui::SmartCode *ui;
    QComboBox* runScript;

    QString projectPath;
    QMap<QTreeWidgetItem*, QString> treeWidgetFiles;
    QMap<SCodeEditor*, QString> codeEditorFiles;

    QVector<QString> unsavedFiles;

    QMap<QString, int> openedTabs;
};

#endif // SMARTCODE_H
