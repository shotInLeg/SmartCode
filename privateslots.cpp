#include "SSmartCode.h"
#include "ui_SSmartCode.h"

void SSmartCode::projectCreated(QString path)
{
    currentPath = path;
    updateTreeView();
    ui->wLeftSide->show();
    ui->aProjectTree->setChecked(true);
}

void SSmartCode::entryCreated(QString type, QString name)
{
    Q_UNUSED(type);
    Q_UNUSED(name);

    updateTreeView();
}

void SSmartCode::codeEditorPosChanged()
{
    int col = codeEditor->textCursor().columnNumber();
    int row = codeEditor->textCursor().blockNumber()+1;

    codeEditorPos->setText(QString::number(row) +
                           "|" + QString::number(col));
}
