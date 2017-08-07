#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QToolBar>
#include <QTreeWidget>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>

namespace Ui {
class SmartCode;
}

class SmartCode : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartCode(QWidget *parent = 0);
    ~SmartCode();

private:
    Ui::SmartCode *ui;
};

#endif // SMARTCODE_H
