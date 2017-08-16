#include "s_code_editor.h"

SCodeEditor::SCodeEditor(QWidget *parent): QWidget(parent)
{
    //QWidget * pe = new QWidget;
    //pe->setMinimumWidth(25);
    //pe->setGeometry(pe->rect().x(), pe->rect().y(), 200, 400);

    //QTextEdit* ed = new QTextEdit;


    lineNumbers = new LineNumberArea(this);
    lineNumbers->setMinimumWidth(25);
    //lineNumbers->setStyleSheet("background: rgb(80,80,80);");

    saveStatus = new SaveStatusArea(this);
    saveStatus->setMinimumWidth(20);
    //saveStatus->setStyleSheet("background: rgb(80,80,80);");

    codeArea = new CodeArea;
    codeArea->setStyleSheet("border: 0px solid black;");


    errorInfo = new ErrorInfoArea(this);
    errorInfo->setMinimumWidth(200);
    errorInfo->setStyleSheet("background: rgba(255,255,255);");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);


    mainLayout->addWidget(lineNumbers);
    mainLayout->addWidget(saveStatus);
    mainLayout->addWidget(codeArea);
    mainLayout->addWidget(errorInfo);

    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 1);
    mainLayout->setStretch(2, 10000);
    mainLayout->setStretch(3, 1);

    this->setLayout(mainLayout);

    connect(codeArea, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumbersWidth(int)));
    connect(codeArea, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumbers(QRect,int)));
    //connect(codeArea, SIGNAL(cursorPositionChanged()), codeArea, SLOT(highlightCurrentLine()));
}

void SCodeEditor::lineNumbersPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumbers);
    painter.fillRect(event->rect(), QBrush(QColor(80,80,80)));


    QTextBlock block = codeArea->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) codeArea->blockBoundingGeometry(block).translated(codeArea->contentOffset()).top();
    int bottom = top + (int) codeArea->blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);

            painter.setPen(Qt::white);
            painter.drawText(10, top, lineNumbers->width(), fontMetrics().height(),
                             Qt::AlignVCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) codeArea->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void SCodeEditor::saveStatusPaintEvent(QPaintEvent *event)
{
    QPainter painter(saveStatus);
    painter.fillRect(event->rect(), QBrush(QColor(80,80,80)));


    QTextBlock block = codeArea->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) codeArea->blockBoundingGeometry(block).translated(codeArea->contentOffset()).top();
    int bottom = top + (int) codeArea->blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            if( unsaveRows.contains(blockNumber) )
            {
                painter.setPen(Qt::white);
                painter.drawText(10, top, saveStatus->width(),
                                 fontMetrics().height(), Qt::AlignVCenter, "*");
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) codeArea->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void SCodeEditor::errorInfoPaintEvent(QPaintEvent *event)
{
    QPainter painter(errorInfo);
    painter.fillRect(event->rect(), QBrush(QColor(255, 255, 255)));


    QTextBlock block = codeArea->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) codeArea->blockBoundingGeometry(block).translated(codeArea->contentOffset()).top();
    int bottom = top + (int) codeArea->blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            if( errors.contains(blockNumber))
            {
                painter.setPen(Qt::white);
                painter.fillRect(QRect(10, top, errorInfo->width(), codeArea->fontMetrics().height()),
                                 QBrush(QColor(255, 0, 0)));

                painter.drawText(10, top, errorInfo->width(),
                                 codeArea->fontMetrics().height(), Qt::AlignVCenter, errors[blockNumber]);
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) codeArea->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

CodeArea *SCodeEditor::codeWidget() const
{
    return codeArea;
}

int SCodeEditor::lineNumbersWidth()
{
    int digits = 1;
    int max = qMax(1, codeArea->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + codeArea->fontMetrics().width(QLatin1Char('9')) * digits;

    return space+10;
}

void SCodeEditor::updateLineNumbers(const QRect& rect, int dy)
{
    if(dy)
    {
        lineNumbers->scroll(0, dy);
        saveStatus->scroll(0, dy);
        errorInfo->scroll(0, dy);
    }
    else
    {
        this->update(0, rect.y(), this->width(), rect.height());
    }

    if (rect.contains(codeArea->viewport()->rect()))
        updateLineNumbersWidth(0);
}

void SCodeEditor::updateLineNumbersWidth(int /*newBlockCount*/)
{
    if(codeArea->blockCount() > 10)
    {
        errors[10] = "a is unused";
        unsaveRows.push_back(10);
    }

    lineNumbers->setMinimumWidth(lineNumbersWidth());
}


CodeArea::CodeArea(QWidget *parent) : QPlainTextEdit(parent)
{
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

void CodeArea::resizeEvent(QResizeEvent *e)
{}


void CodeArea::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(110,110,110, 125).lighter(160);

        //selection
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}
