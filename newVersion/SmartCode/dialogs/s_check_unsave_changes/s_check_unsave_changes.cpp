#include "s_check_unsave_changes.h"
#include "ui_s_check_unsave_changes.h"

SCheckUnsaveChanges::SCheckUnsaveChanges(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCheckUnsaveChanges)
{
    ui->setupUi(this);
}

SCheckUnsaveChanges::SCheckUnsaveChanges(const QVector<QString> &unsaveFiles,
                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCheckUnsaveChanges)
{
    ui->setupUi(this);

    this->unsaveFiles = unsaveFiles;

    // Задаем настрокйи таблице с файлами
    ui->twListUnsaveFiles->setRowCount(this->unsaveFiles.size());
    ui->twListUnsaveFiles->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->twListUnsaveFiles->horizontalHeader()->setStretchLastSection(true);

    // Заполняем таблицу с файлами
    int i = 0;
    for(const QString& file : this->unsaveFiles)
    {
        QCheckBox* checker = new QCheckBox;
        checker->setChecked(true);
        this->checkers.push_back(checker);

        ui->twListUnsaveFiles->setCellWidget(i, 0, checker);
        ui->twListUnsaveFiles->setItem(i, 1, new QTableWidgetItem(file));

        i++;
    }
}

SCheckUnsaveChanges::~SCheckUnsaveChanges()
{
    delete ui;
}

void SCheckUnsaveChanges::on_bSave_clicked()
{
    QVector<QString> filesToSave;
    for(int i = 0; i < checkers.size(); i++)
    {
        if(checkers.at(i)->isChecked())
        {
            filesToSave.push_back(unsaveFiles.at(i));
        }
    }

    emit saveFiles(filesToSave);
    this->close();
}

void SCheckUnsaveChanges::on_bNotSave_clicked()
{
    QVector<QString> filesToNotSave;
    for(int i = 0; i < checkers.size(); i++)
    {
        if(checkers.at(i)->isChecked())
        {
            filesToNotSave.push_back(unsaveFiles.at(i));
        }
    }

    emit notSave(filesToNotSave);
    this->close();
}

void SCheckUnsaveChanges::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}

void SCheckUnsaveChanges::on_bViewChanges_clicked()
{
    int currentRow = ui->twListUnsaveFiles->currentRow();

    if(currentRow > 0 && currentRow < unsaveFiles.size())
    {
        emit viewChanges(unsaveFiles.at(currentRow));
    }
}
