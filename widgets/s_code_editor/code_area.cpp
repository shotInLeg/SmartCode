#include "s_code_editor.h"

CodeArea::CodeArea(SCodeEditor *parent) : QPlainTextEdit(parent), c(0)
{
    this->codeEditor = parent;
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

QCompleter *CodeArea::completer() const
{
    return this->c;
}

void CodeArea::setCompleter(QCompleter *completer)
{
    if (this->c)
        QObject::disconnect(this->c, 0, this, 0);

    this->c = completer;

    if (!completer)
        return;

    this->c->setWidget(this);
    this->c->setCompletionMode(QCompleter::PopupCompletion);
    this->c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(this->c, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QString CodeArea::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeArea::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                        || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    c->popup()->setFont(QFont("Monaco", 12));
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}

void CodeArea::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);

    QPlainTextEdit::focusInEvent(e);
}

void CodeArea::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
}

void CodeArea::insertCompletion(const QString &completion)
{
    if (c->widget() != this)
        return;

    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}


void CodeArea::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(221, 221, 221);

        //selection
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}
