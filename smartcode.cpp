#include "smartcode.h"
#include "ui_smartcode.h"

SmartCode::SmartCode(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::SmartCode)
{
    ui->setupUi(this);

    ui->pteCodeEdit->setFont( QFont("Consolas", 11) );
    highlighter = new Highlighter( ui->pteCodeEdit->document() );
}

SmartCode::~SmartCode()
{
    delete ui;
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
