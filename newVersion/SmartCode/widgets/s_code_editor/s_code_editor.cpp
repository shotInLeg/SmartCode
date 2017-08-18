#include "s_code_editor.h"

SCodeEditor::SCodeEditor(QWidget *parent): QWidget(parent)
{
    //QWidget * pe = new QWidget;
    //pe->setMinimumWidth(25);
    //pe->setGeometry(pe->rect().x(), pe->rect().y(), 200, 400);

    //QTextEdit* ed = new QTextEdit;
    maxSymbolsInRow = 100;

    lineNumbers = new LineNumberArea(this);
    lineNumbers->setMinimumWidth(25);
    //lineNumbers->setStyleSheet("background: rgb(80,80,80);");

    saveStatus = new SaveStatusArea(this);
    saveStatus->setMinimumWidth(13);
    //saveStatus->setStyleSheet("background: rgb(80,80,80);");

    codeArea = new CodeArea(this);
    codeArea->setMinimumWidth(480);
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
    connect(codeArea, SIGNAL(textChanged()), this, SLOT(codeAreaChanged()));
    //connect(codeArea, SIGNAL(cursorPositionChanged()), codeArea, SLOT(highlightCurrentLine()));
}

SCodeEditor::~SCodeEditor()
{
    emit closed(this, codeArea->toPlainText());
    delete lineNumbers;
    delete saveStatus;
    delete codeArea;
    delete errorInfo;
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

                painter.fillRect(QRect(10, top, saveStatus->width(), codeArea->fontMetrics().height()),
                                 QBrush(QColor(255, 0, 0)));
            }

            if( saveRows.contains(blockNumber) )
            {
                painter.setPen(Qt::white);

                painter.fillRect(QRect(10, top, saveStatus->width(), codeArea->fontMetrics().height()),
                                 QBrush(QColor(0, 255, 0)));
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) codeArea->blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void SCodeEditor::codeAreaPaintEvent(QPaintEvent *event)
{
    QPainter linePainter(codeArea->viewport());
    linePainter.setPen(Qt::gray);

    int y1 = event->rect().topLeft().y();
    int y2 = event->rect().bottomLeft().y();
    int x = event->rect().topLeft().x();
    x += codeArea->fontMetrics().width("x") * maxSymbolsInRow;

    qDebug() << x << " " << y1 << " " << x << " " << y2;

    linePainter.drawLine(x, 0, x, 500);
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

void SCodeEditor::setMaxSymbolsInRow(int maxSymbols)
{
    maxSymbolsInRow = maxSymbols;
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
    if(codeArea->blockCount() > 24)
    {
        errors[24] = "expression need brackets";
    }


    saveRows.clear();
    for(int i = 0; i < codeArea->blockCount(); i++)
    {
        if(i == 8)
            continue;
        saveRows.push_back(i);
    }

    unsaveRows.clear();
    unsaveRows.push_back(8);

    lineNumbers->setMinimumWidth(lineNumbersWidth());
}

void SCodeEditor::codeAreaChanged()
{
    emit changed(this);
}
