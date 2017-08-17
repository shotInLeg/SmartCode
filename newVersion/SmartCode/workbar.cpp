#include "smartcode.h"
#include "ui_smartcode.h"

SCodeEditor *SmartCode::openTab(const QString &tabName)
{

    QCompleter* completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/completer/resources/completer/lgc.cw", completer));
    //completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    //completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setWrapAround(false);

    SCodeEditor * te = new SCodeEditor(this);
    te->codeWidget()->setTabStopWidth ( 33 );
    te->codeWidget()->setCompleter(completer);

    SHighlighter * h = new SHighlighter(te->codeWidget()->document());
    h->updateHighlightRules(":/highlighter/resources/highlighter/lgc.hp");
    te->codeWidget()->setFont(QFont("Fira Sans"));

    QHBoxLayout * nl = new QHBoxLayout(this);
    nl->setMargin(0);

    QWidget * nw = new QWidget(this);
    nw->setLayout(nl);
    nl->addWidget(te);

    ui->twOpenedFiles->addTab(nw, tabName);

    return te;
}
