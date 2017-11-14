#include "s_confirm_remove.h"
#include "ui_s_confirm_remove.h"

SConfirmRemove::SConfirmRemove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SConfirmRemove)
{
    ui->setupUi(this);
}

SConfirmRemove::SConfirmRemove(const QVector<QString> &filesToRemove,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SConfirmRemove)
{
    ui->setupUi(this);
    this->filesToRemove = filesToRemove;

    // Задаем настрокйи таблице с файлами
    ui->twListFilesToRemove->setRowCount(this->filesToRemove.size());
    ui->twListFilesToRemove->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->twListFilesToRemove->horizontalHeader()->setStretchLastSection(true);

    int i = 0;
    for(const QString& file : this->filesToRemove)
    {
        QCheckBox* checker = new QCheckBox;
        checker->setChecked(true);
        this->checkers.push_back(checker);

        ui->twListFilesToRemove->setCellWidget(i, 0, checker);
        ui->twListFilesToRemove->setItem(i, 1, new QTableWidgetItem(file));

        i++;
    }
}

SConfirmRemove::~SConfirmRemove()
{
    delete ui;
}

void SConfirmRemove::on_bRemoveChecked_clicked()
{
    QVector<QString> filesToRemove;
    for(int i = 0; i < checkers.size(); i++)
    {
        if(checkers.at(i)->isChecked())
        {
            filesToRemove.push_back(this->filesToRemove.at(i));
        }
    }

    emit removeFiles(filesToRemove);
    this->close();
}

void SConfirmRemove::on_bCheckAll_clicked()
{
    for(QCheckBox* checker : checkers)
    {
        checker->setChecked(true);
    }
}

void SConfirmRemove::on_bRevertChecked_clicked()
{
    for(QCheckBox* checker : checkers)
    {
        checker->setChecked( !checker->isChecked() );
    }
}

void SConfirmRemove::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}
