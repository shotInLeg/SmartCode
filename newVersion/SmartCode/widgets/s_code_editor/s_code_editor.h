#ifndef SCODEEDITOR_H
#define SCODEEDITOR_H

#include <QPainter>
#include <QTextBlock>
#include <QPlainTextEdit>
#include <QObject>
#include <QCompleter>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QLabel>
#include <QPushButton>

#include <QDebug>
#include <QLayout>
#include <QSpacerItem>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class BreakpointArea;
class LineNumberArea;
class SaveStatusArea;
class ManageIndicatorsArea;
class GitInfoArea;
class ErrorInfoArea;
class CodeArea;

class SCodeEditor : public QWidget
{
    Q_OBJECT

public:
    SCodeEditor(QWidget *parent);
    virtual ~SCodeEditor();

public:
    void lineNumbersPaintEvent(QPaintEvent *event);
    void saveStatusPaintEvent(QPaintEvent* event);
    void codeAreaPaintEvent(QPaintEvent *event);
    void errorInfoPaintEvent(QPaintEvent* event);
    int lineNumbersWidth();

public:
    void markLineIsUnsaved(int row);
    void markLineIsSaved(int row);
    void markLineIsWrong(int row, const QString& text);
    void setMaxSymbolsInRow(int maxSymbols);

    CodeArea *codeWidget() const;

private slots:
    void updateLineNumbers(const QRect &rect, int dy);
    void updateLineNumbersWidth(int);

    void codeAreaChanged();

signals:
    void closed(SCodeEditor*, QString);
    void changed(SCodeEditor*);

private:
    QWidget* lineNumbers;
    QWidget* saveStatus;
    CodeArea* codeArea;
    QWidget* errorInfo;

    QVector<int> unsaveRows;
    QVector<int> saveRows;
    QMap<int, QString> errors;
    int maxSymbolsInRow;
};

class CodeArea : public QPlainTextEdit
{
    Q_OBJECT

public:
    friend class SCodeEditor;

    CodeArea(SCodeEditor *parent = 0);

public:
    QCompleter *completer() const;

    void setCompleter(QCompleter *completer);

private:
    QString textUnderCursor() const;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent* e) override {
        codeEditor->codeAreaPaintEvent(e);
        QPlainTextEdit::paintEvent(e);
    }

private slots:
    void insertCompletion(const QString &completion);

public slots:
    void highlightCurrentLine();

private:
    QCompleter *c;
    SCodeEditor *codeEditor;
};


class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(SCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumbersWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumbersPaintEvent(event);
    }

private:
    SCodeEditor *codeEditor;
};

class SaveStatusArea : public QWidget
{
    Q_OBJECT

public:
    SaveStatusArea(SCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->saveStatusPaintEvent(event);
    }

private:
    SCodeEditor *codeEditor;
};

class ErrorInfoArea : public QWidget
{
    Q_OBJECT

public:
    ErrorInfoArea(SCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->errorInfoPaintEvent(event);
    }

private:
    SCodeEditor *codeEditor;
};

class BreakpointArea : public QWidget
{
public:
    BreakpointArea()
    {}

protected:
    void paintEvent(QPaintEvent *event);
};




class ManageIndicatorsArea : public QWidget
{
public:
    ManageIndicatorsArea()
    {}

protected:
    void paintEvent(QPaintEvent *event);
};

class GitInfoArea : public QWidget
{
public:
    GitInfoArea()
    {}

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CODEEDITOR_H
