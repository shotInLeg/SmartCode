#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QFontDialog>
#include <QFile>
#include <QFileDialog>

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





private:
    Ui::SmartCode *ui;

    Highlighter *highlighter;
};

#endif // SMARTCODE_H
