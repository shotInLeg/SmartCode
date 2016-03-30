#include "smartcode.h"
#include "ui_smartcode.h"

SmartCode::SmartCode(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);

    ui->pteCodeEdit->setTabStopWidth ( 33 );
    ui->pteCodeEdit->setFont( QFont("Consolas", 11) );
    highlighter = new Highlighter( ui->pteCodeEdit->document() );
}

SmartCode::~SmartCode()
{
    delete ui;
}

void SmartCode::paintEvent ( QPaintEvent * event )
{
    /*QPainter painter;
    painter.begin( ui->pteCodeEdit->viewport() );
    painter.drawLine(0,0,300, 50);

    QRect r = ui->pteCodeEdit->cursorRect();
    r.setX( 0 );
    r.setWidth( ui->pteCodeEdit->viewport()->width() );
    painter.fillRect( r, QBrush( Qt::blue ) );*/
}

void SmartCode::on_aFontSettings_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, ui->pteCodeEdit->font(), this);
    if (ok)
    {
        ui->pteCodeEdit->setFont( font );
    }
}


void SmartCode::on_pteCodeEdit_cursorPositionChanged()
{
    int lineNumber = ui->pteCodeEdit->textCursor().blockNumber();
    QTextBlock block = ui->pteCodeEdit->textCursor().block();

    qDebug() << lineNumber;
    ui->pteCodeEdit->document()->findBlockByLineNumber( lineNumber );
}

void SmartCode::on_aMakeCPP_triggered()
{
    QString textFile = ui->pteCodeEdit->toPlainText();

    ACP parser;
    QVector<QString> tokens = parser.parse(textFile);


    for(int i = 0; i < tokens.size(); i++)
    {
        qDebug() << tokens.at(i);
    }

}

void SmartCode::on_aSaveFile_triggered()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("Сохранить файл..."),"",tr("Archi Source File (*.arc)"));

    QFile saveFile(dir);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    saveFile.write( QByteArray().append(ui->pteCodeEdit->toPlainText()) );

    saveFile.close();
}

void SmartCode::on_aOpenFile_triggered()
{
    QString dir = QFileDialog::getOpenFileName(this, tr("Открыть файл..."),"",tr("Archi Source File (*.arc)"));

    QFile openFile(dir);
    if(!openFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray bytesFromFile = openFile.readAll();

    ui->pteCodeEdit->setPlainText( QString::fromStdString(bytesFromFile.toStdString()) );

    openFile.close();
}
