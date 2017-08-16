#ifndef SMARTCODE_H
#define SMARTCODE_H

#include <QMainWindow>
#include <QToolBar>
#include <QTreeWidget>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>

#include <QTextEdit>

#include <QDir>
#include <QFileInfoList>
#include <QFont>
#include <QFontDatabase>

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

private:
    void showDirTree(const QString& dirPath);
    void recoursiveShowDirTree(const QDir& dir,
                               QTreeWidgetItem *item = nullptr);

    SCodeEditor *openTab(const QString& tabName);

private:
    Ui::SmartCode *ui;
};

#endif // SMARTCODE_H
