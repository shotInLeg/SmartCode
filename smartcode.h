#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QFontDialog>

#include "Highlighter/highlighter.h"

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
    void on_aFontSettings_triggered();

private:
    Ui::SmartCode *ui;

    Highlighter *highlighter;
};

#endif // SMARTCODE_H
