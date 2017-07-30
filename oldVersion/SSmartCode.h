#ifndef SSMARTCODE_H
#define SSMARTCODE_H

#include <QMainWindow>
#include <QFontDialog>
#include <QFile>
#include <QFileDialog>
#include <QDirModel>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QPushButton>
#include <QTreeView>

#include "SCodeEditor/SCodeEditor.h"
#include "SCodeEditor/SHighlighter/SHighlighter.h"

#include "SCreateProjectForm/SCreateProjectForm.h"
#include "SCreateNewEntryForm/SCreateNewEntryForm.h"
#include "SSaveChangesForm/SSaveChangesForm.h"

namespace Ui {
class SSmartCode;
}

class SSmartCode : public QMainWindow
{
    Q_OBJECT

public:
    explicit SSmartCode(QWidget *parent = 0);
    ~SSmartCode();


private slots:
    //Menu MenuActions.cpp
    void on_aCreateProject_triggered();
    void on_aOpenProject_triggered();
    void on_aSaveProject_triggered();
    void on_aFindReplace_triggered();
    void on_aPanelFindReplace_triggered();
    void on_aTerminal_triggered();
    void on_aProjectTree_triggered();

    //LeftBar LeftBarSlots.cpp
    void on_bAddFile_clicked();
    void on_tvProjectFiles_itemDoubleClicked(QTreeWidgetItem *item, int column);

    //Window
    void closeEvent(QCloseEvent* event);

private slots: //PrivateSlots.cpp
    void projectCreated(QString path);
    void entryCreated(QString type, QString name);
    void codeEditorPosChanged();
    void currentFileChanged();
    void saveAndClose();
    void notSaveAndClose();

private: //PrivateFunc.cpp
    void setupCodeEditor();
    void setupTreeView();
    void setupRightBar();
    void setupBottomBar();
    void setupLeftBar();

    void updateTreeView();

    void cashCurrentDocument();
    void setHighlightPage(const QString& filename);
    void loadFileToCodeEditor(const QString& filename);



    //Recoursive method to print Tree start in dir
    void printDir(const QDir &dir, QTreeWidgetItem * item );
    //Method to get full path from root project to item
    QString dreelUp( QTreeWidgetItem * item );
private:

//Windows
    Ui::SSmartCode *ui;

//Widgets
    SCodeEditor * codeEditor;
    SHighlighter * highlighter;
    QLabel * codeEditorPos;

//Current State
    QString currentPath;
    QString currentFile;
    QMap<QString, QByteArray> cashedFiles;
    QVector<QString> unsavesFiles;
};

#endif // SSMARTCODE_H
