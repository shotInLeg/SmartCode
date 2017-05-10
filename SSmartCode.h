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
#include "SCreateNewEntry/SCreateNewEntry.h"

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
    void on_aCreateProject_triggered();

    void projectCreated(QString path);
    void entryCreated(QString type, QString name);

    void on_bAddFile_clicked();

    void on_tvProjectFiles_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_aOpenProject_triggered();

private:
    void setupCodeEditor();
    void setupTreeView();

    void updateTreeView();

    void printDir(const QDir &dir, QTreeWidgetItem * item );
    QString dreelUp( QTreeWidgetItem * item );
private:

//Windows
    Ui::SSmartCode *ui;

//Widgets
    SCodeEditor * codeEditor;
    SHighlighter * highlighter;

//Models
    QDirModel * dirModel;

//Current State
    QString currentPath;
    QString currentFile;
    QVector<QString> openedFiles;
};

#endif // SSMARTCODE_H
