#include "s_add_new_entry.h"
#include "ui_s_add_new_entry.h"

SAddNewEntry::SAddNewEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAddNewEntry)
{
    ui->setupUi(this);
}

SAddNewEntry::SAddNewEntry(const QVector<QPair<QString, QString> > &types,
                           const QString &basePath,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAddNewEntry)
{
    ui->setupUi(this);

    this->types = types;
    this->basePath = basePath;

    //Заполняем поле выбора типа
    for(const QPair<QString, QString>& type : types)
    {
        ui->cbEntryType->addItem(type.second);
    }
}

SAddNewEntry::~SAddNewEntry()
{
    delete ui;
}

void SAddNewEntry::on_bAdd_clicked()
{
    int typeIndex = ui->cbEntryType->currentIndex();
    QString type = types.at(typeIndex).first;

    QString choosenEntry = ui->eChoosenPath->text();
    QString entryPath = ui->eEntryPath->text();
    QString entryName = ui->eEntryName->text();

    emit addEntry(type, choosenEntry, entryPath, entryName);
    this->close();
}

void SAddNewEntry::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}

void SAddNewEntry::on_bChoosePath_clicked()
{
    int typeIndex = ui->cbEntryType->currentIndex();
    QString type = types.at(typeIndex).first;

    QString choosenEntry = "";
    if(type == "*")
    {
        choosenEntry = QFileDialog::getExistingDirectory(this,
                                                         "$SelectDirForAddToProject",
                                                         basePath);
    }
    else
    {
        choosenEntry = QFileDialog::getOpenFileName(this,
                                                    "$SelectDirForAddToProject",
                                                    basePath, type);
    }

    ui->eChoosenPath->setText(choosenEntry);
}

void SAddNewEntry::on_bChooseEntryPath_clicked()
{
    QString entryPath = QFileDialog::getExistingDirectory(this,
                                                          "$SelectDirForAddToProject",
                                                          basePath);
    ui->eEntryPath->setText(entryPath);
}

void SAddNewEntry::on_cbEntryType_currentIndexChanged(int)
{
    ui->eChoosenPath->clear();
}
