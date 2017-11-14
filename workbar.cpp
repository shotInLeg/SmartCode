#include "smartcode.h"
#include "ui_smartcode.h"

#include "dialogs/s_check_unsave_changes/s_check_unsave_changes.h"

SCodeEditor *SmartCode::openTab(const QString &tabName, const QString& filePath)
{
    QCompleter* completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/completer/resources/completer/lgc.cw", completer));

    SCodeEditor * te = new SCodeEditor(this);
    te->codeWidget()->setTabStopWidth ( 33 );
    te->codeWidget()->setCompleter(completer);

    SHighlighter * h = new SHighlighter(te->codeWidget()->document());
    h->updateHighlightRules(":/highlighter/resources/highlighter/lgc.hp");
    //te->codeWidget()->setFont(QFont("Fira Sans", 14));
    te->codeWidget()->setFont(QFont("Monaco", 12));

    ui->twOpenedFiles->addTab(te, tabName);
    ui->twOpenedFiles->setCurrentIndex(ui->twOpenedFiles->count()-1);
    openedTabs[filePath] = ui->twOpenedFiles->currentIndex();

    return te;
}

void SmartCode::viewFileInCodeArea(SCodeEditor* editor, const QString &filePath)
{
    QFile openFile(filePath);
    if(!openFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл "
                                                 "для четния, проверьте "
                                                 "права доступа");
    }
    QByteArray bytesFromFile = openFile.readAll();
    openFile.close();

    editor->codeWidget()->setPlainText(QString(bytesFromFile));
}

void SmartCode::saveDataFromCodeArea(SCodeEditor *editor, const QString &filePath)
{
    QFile saveFile(filePath);
    if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray data;
        data = data.append(editor->codeWidget()->toPlainText());
        saveFile.write(data);
    }
    saveFile.close();
}

void SmartCode::on_twOpenedFiles_tabCloseRequested(int index)
{
    SCodeEditor* w = dynamic_cast<SCodeEditor*>(ui->twOpenedFiles->widget(index));

    QString path = "";
    if(codeEditorFiles.contains(w))
    {
        path = codeEditorFiles[w];
    }

    if(unsavedFiles.contains(path))
    {
        SCheckUnsaveChanges* check = new SCheckUnsaveChanges(QVector<QString>{ path }, this);
        QObject::connect(check,
                         SIGNAL(saveFiles(QVector<QString>)),
                         this,
                         SLOT(closeTabSave(QVector<QString>)));
        QObject::connect(check,
                         SIGNAL(notSave(QVector<QString>)),
                         this,
                         SLOT(closeTabNotSave(QVector<QString>)));
        QObject::connect(check,
                         SIGNAL(destroyed(QObject*)),
                         check,
                         SLOT(deleteLater()));
        check->show();
    }
    else
    {
        ui->twOpenedFiles->removeTab(index);
    }
}
