#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QFontDialog>
#include <QFile>
#include <QFileDialog>
#include <QDirModel>
#include <QTreeWidgetItem>
#include <QPainter>

#include "Highlighter/highlighter.h"
#include "ACC/acp.h"

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
    void paintEvent( QPaintEvent * event );

    //Текстовое поле
    void on_pteCodeEdit_cursorPositionChanged();


    //Меню "Файл"
    void on_aOpenFile_triggered();
    void on_aSaveFile_triggered();

    //Меню "Вид"
    void on_aFontSettings_triggered();

    //Меню "Запуск"
    void on_aMakeCPP_triggered();

    void on_aOpenProject_triggered();

    void on_aCreateProject_triggered();

    void on_tvProjectStruct_doubleClicked(const QModelIndex &index);

    void on_aCreateFile_triggered();

    void on_aSave_triggered();

    void updateTreeWidget();

    void printDir(const QDir& dir, QTreeWidgetItem *item);

    void on_tvProjectStruct_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::SmartCode *ui;
    QDirModel * dirModel;
    Highlighter *highlighter;

    QString currentPath;
    QString currentFile;
};

#endif // SMARTCODE_H
